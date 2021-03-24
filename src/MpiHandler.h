
#ifndef VIRUS_SPREADING_MODEL_MPIHANDLER_H
#define VIRUS_SPREADING_MODEL_MPIHANDLER_H


#include <malloc.h>
#include <functional>
#include "InputParser.h"
#include "Infected.h"
#include "JsonHandler.h"
#include "World.h"
#include "mpi.h"
/**
 * Wrapper class used to handle all MPI communication between processes.
 */
class MpiHandler {
private:
    /**
     * Rank of the communicator
     */
    int my_rank;
    /**
     * Number of the communicators in the world
     */
    int world_size;
    /**
     * Number of individuals assigned to this world representation
     */
    int* individuals_split_accumulator = (int*)malloc(sizeof(int));
    /**
     * Size of a message that passes an integer number
     */
    int* message_size = (int*)malloc(sizeof(int));
    /**
     * Size of a message that passes a char array
     */
    char* received_message = nullptr;
    MPI_Comm communicator;
public:
    int getMyRank() const;

    int getWorldSize() const;

    MpiHandler(int myRank, int worldSize, MPI_Comm communicator);

    virtual ~MpiHandler();
    char* getReceivedMessage();
    /**
     * Used to split individuals between processes.
     * @param inputParser Used to parse the configuration file and obtain the total number of individuals
     * @return Returns the number of individuals assigned to the calling process
     */
    int split_individuals(InputParser &inputParser);
    /**
     * Used to broadcast the receiving message to every other process in the world
     */
    void broadcast();

    /**
     * Establishes a ring based communication between all the processes, processes communicate to the one that has rank
     * immediately after theirs
     * @param jsonHandler Used to handle serialization and deserialization
     * @param world World representation of the calling process
     * @param fn Function pointer to the type of message exchange decided (infected diffusion, stats diffusion)
     */
    void ring(JsonHandler &jsonHandler, World *world, void(JsonHandler::*fn)(char*, World*));
private:
    void allocateReceivedMessage();



};


#endif //VIRUS_SPREADING_MODEL_MPIHANDLER_H
