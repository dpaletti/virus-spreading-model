#include <utility>
#include <cmath>
#include <mpi.h>
#include "InputParser.h"
#include "Cell.h"
#include "Infected.h"

// TODO: move all methods except serialize and deserialize to a coordination (think of a better name) class
// TODO: move serialize and deserialize to a helper file (no state)

int split_individuals(int my_rank, InputParser *inputParser, int world_size) {

    int accumulator;
    int individuals = std::floor(inputParser->getIndividualsNumber() / world_size);
    if (my_rank == 0) {
        MPI_Send(&individuals, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&accumulator, 1, MPI_INT, world_size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        individuals += inputParser->getIndividualsNumber() - accumulator;
    } else {
        int destination = my_rank + 1;
        MPI_Recv(&accumulator, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        accumulator += individuals;
        if (my_rank == world_size)
            destination = 0;
        MPI_Send(&accumulator, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    }
    return individuals;

}

rapidjson::StringBuffer serialize_list(const std::vector<Infected>& infected_list){
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    writer.StartArray();
    for (const auto &item : infected_list) {
        item.Serialize(writer);
    }
    writer.EndArray();
   return sb;

}
std::string spread_infected(int my_rank, int world_size, rapidjson::StringBuffer& serialized, std::vector<Infected> infected_list) {
    std::string buf;
    MPI_Status status;
    int messageSize;
    rapidjson::Document document;
    if (my_rank == 0) {
        MPI_Send(serialized.GetString(), serialized.GetSize(), MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
        MPI_Probe(world_size - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &messageSize);
        MPI_Recv(&buf, messageSize, MPI_CHAR, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Probe(my_rank - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &messageSize);
        MPI_Recv(&buf, messageSize, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        document.Parse(buf.c_str());
        for (rapidjson::Value::ConstMemberIterator iterator = document.MemberBegin();
             iterator != document.MemberEnd(); ++iterator) {
            auto *temp_infected = new Infected();
            temp_infected->Deserialize(iterator->value);
            infected_list.push_back(*temp_infected);
        }
        serialized = serialize_list(infected_list);
        MPI_Send((void *) serialized.GetString(), serialized.GetSize(), MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
    }
    return buf;
}

void broadcast_global_infected(int my_rank, std::string current_serialized_infected){
    MPI_Status status;
    int messageSize;
    if(my_rank == 0){
        MPI_Bcast(&current_serialized_infected,current_serialized_infected.size(),MPI_CHAR,0,MPI_COMM_WORLD);
    }else{
        MPI_Probe(0,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status,MPI_CHAR,&messageSize);
        MPI_Bcast(&current_serialized_infected,messageSize,MPI_CHAR,0,MPI_COMM_WORLD);
    }
}

std::vector<Infected> deserialize_list(const std::string& current_serialized_infected){
    std::vector<Infected> infected_list;
    rapidjson::Document document;

    document.Parse(current_serialized_infected.c_str());
    for (rapidjson::Value :: ConstMemberIterator iterator = document.MemberBegin(); iterator != document.MemberEnd();++iterator) {
        auto *temp_infected = new Infected();
        temp_infected->Deserialize(iterator->value);
        infected_list.push_back(*temp_infected);
    }
    return infected_list;

}