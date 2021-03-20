
#include <cmath>
#include <mpi.h>
#include "MpiHandler.h"
#include "helper.h"

char *MpiHandler::getCurrentSerializedInfected() {
    return current_serialized_infected;
}

int MpiHandler::split_individuals(InputParser *inputParser) {
    int individuals = std::floor(inputParser->getIndividualsNumber() / world_size);
    if (my_rank == 0) {
        MPI_Send(&individuals, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(individuals_split_accumulator, 1, MPI_INT, world_size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        individuals += inputParser->getIndividualsNumber() - *individuals_split_accumulator;
    } else {
        int destination = my_rank + 1;
        MPI_Recv(individuals_split_accumulator, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        *individuals_split_accumulator += individuals;
        if (my_rank == world_size-1)
            destination = 0;
        MPI_Send(individuals_split_accumulator, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    }
    return individuals;
}

void MpiHandler::spread_infected(rapidjson::StringBuffer &serialized,
                                 std::vector<Infected> infected_list) {

    MPI_Status status;
    int destination = my_rank+1;
    rapidjson::Document document;
    if (my_rank == 0) {
        MPI_Send(serialized.GetString(), strlen(serialized.GetString()), MPI_CHAR, destination, 0, MPI_COMM_WORLD);
        MPI_Probe(world_size - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, message_size);
        allocateInfected();
        MPI_Recv(current_serialized_infected, *message_size, MPI_CHAR, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        Infected *temp_infected;
        MPI_Probe(my_rank - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, message_size);
        allocateInfected();
        MPI_Recv(current_serialized_infected, *message_size, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        document.Parse<rapidjson::kParseStopWhenDoneFlag>((const char *) current_serialized_infected);
        for(auto& e : document.FindMember("infected")->value.GetArray()){
            try {
                temp_infected = new Infected();
            }catch(std::bad_alloc&){
                printf("\nBad Alloc in spread infected at rank %d\n", my_rank);
                abort();
            }
            temp_infected->Deserialize(e.GetObject());
            infected_list.push_back(*temp_infected);
        }
        serialized = serialize_list(infected_list);
        if (my_rank == world_size-1)
            destination = 0;
        MPI_Send((void *) serialized.GetString(), serialized.GetSize(), MPI_CHAR, destination, 0, MPI_COMM_WORLD);
    }
    current_serialized_infected[*message_size] = '\0';

}

void MpiHandler::broadcast_global_infected() {
    MPI_Status status;
    if(my_rank == 0){
        MPI_Bcast(current_serialized_infected, strlen(current_serialized_infected), MPI_CHAR, 0, MPI_COMM_WORLD);
    }else{
        MPI_Probe(0,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status,MPI_CHAR,message_size);
        allocateInfected();
        printf("\n\n\nMessage Size in broadcast: %d\n\n\n", *message_size);
        MPI_Bcast(current_serialized_infected,*message_size,MPI_CHAR,0,MPI_COMM_WORLD);
        (current_serialized_infected)[*message_size] = '\0';
    }

}

void MpiHandler::allocateInfected() {
    if (current_serialized_infected == nullptr)
        current_serialized_infected = (char*)malloc(sizeof(char)* ((*message_size)+1));
    else
        current_serialized_infected = (char*)realloc(current_serialized_infected, sizeof(char)*((*message_size)+1));

}

MpiHandler::MpiHandler(int myRank, int worldSize) : my_rank(myRank), world_size(worldSize) {}

MpiHandler::~MpiHandler() {
    free(individuals_split_accumulator);
    free(message_size);
    free(current_serialized_infected);

}

