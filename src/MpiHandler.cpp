
#include <cmath>
#include <mpi.h>
#include "MpiHandler.h"
#include "JsonHandler.h"
#include "World.h"

char *MpiHandler::getReceivedMessage() {
    return received_message;
}

int MpiHandler::split_individuals(InputParser &inputParser) {
    int individuals = std::floor(inputParser.getIndividualsNumber() / world_size);
    if (my_rank == 0) {
        MPI_Send(&individuals, 1, MPI_INT, 1, 0, communicator);
        MPI_Recv(individuals_split_accumulator, 1, MPI_INT, world_size-1, 0, communicator, MPI_STATUS_IGNORE);
        individuals += inputParser.getIndividualsNumber() - *individuals_split_accumulator;
    } else {
        int destination = my_rank + 1;
        MPI_Recv(individuals_split_accumulator, 1, MPI_INT, my_rank - 1, 0, communicator, MPI_STATUS_IGNORE);
        *individuals_split_accumulator += individuals;
        if (my_rank == world_size-1)
            destination = 0;
        MPI_Send(individuals_split_accumulator, 1, MPI_INT, destination, 0, communicator);
    }
    return individuals;
}


void MpiHandler::broadcast() {
    *message_size = strlen(received_message);
    MPI_Bcast(message_size, 1, MPI_INT, 0, communicator);
    if (my_rank != 0)
        allocateReceivedMessage();
    MPI_Bcast(received_message, *message_size, MPI_CHAR, 0, communicator);
}

void MpiHandler::allocateReceivedMessage() {
    if (received_message == nullptr)
        received_message = (char*)malloc(sizeof(char) * ((*message_size) + 1));
    else
        received_message = (char*)realloc(received_message, sizeof(char) * ((*message_size) + 1));

}

MpiHandler::MpiHandler(int myRank, int worldSize, MPI_Comm communicator) : my_rank(myRank), world_size(worldSize), communicator(communicator){}

MpiHandler::~MpiHandler() {
    free(individuals_split_accumulator);
    free(message_size);
    free(received_message);

}

int MpiHandler::getMyRank() const {
    return my_rank;
}

int MpiHandler::getWorldSize() const {
    return world_size;
}

void MpiHandler::ring(JsonHandler &jsonHandler, World *world, void(JsonHandler::*fn)(char*, World*)) {
    MPI_Status status;
    int destination = my_rank+1;
    std::string serialized = jsonHandler.getSerialized();
    if (my_rank == 0) {
        MPI_Send(serialized.c_str(), strlen(serialized.c_str()), MPI_CHAR, destination, 0, communicator);
        MPI_Probe(world_size - 1, 0, communicator, &status);
        MPI_Get_count(&status, MPI_CHAR, message_size);
        allocateReceivedMessage();
        MPI_Recv(received_message, *message_size, MPI_CHAR, world_size - 1, 0, communicator, MPI_STATUS_IGNORE);
    } else {
        MPI_Probe(my_rank - 1, 0, communicator, &status);
        MPI_Get_count(&status, MPI_CHAR, message_size);
        allocateReceivedMessage();
        MPI_Recv(received_message, *message_size, MPI_CHAR, my_rank - 1, 0, communicator, MPI_STATUS_IGNORE);
        ((&jsonHandler)->*fn)(received_message, world);
        if (my_rank == world_size-1)
            destination = 0;
        MPI_Send((void *) jsonHandler.getSerialized().c_str(), strlen(jsonHandler.getSerialized().c_str()), MPI_CHAR, destination, 0, communicator);
    }
    received_message[*message_size] = '\0';
}



