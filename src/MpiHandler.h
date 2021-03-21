
#ifndef VIRUS_SPREADING_MODEL_MPIHANDLER_H
#define VIRUS_SPREADING_MODEL_MPIHANDLER_H


#include <malloc.h>
#include <functional>
#include "InputParser.h"
#include "Infected.h"
#include "JsonHandler.h"
#include "World.h"

class MpiHandler {
private:
    int my_rank;
    int world_size;
    int* individuals_split_accumulator = (int*)malloc(sizeof(int));
    int* message_size = (int*)malloc(sizeof(int));
    char* received_message = nullptr;
public:
    int getMyRank() const;

    int getWorldSize() const;

    MpiHandler(int myRank, int worldSize);

    virtual ~MpiHandler();

    char* getReceivedMessage();
    int split_individuals(InputParser &inputParser);
    void broadcast();

    void ring(JsonHandler &jsonHandler, World *world, void(JsonHandler::*fn)(char*, World*));
private:
    void allocateReceivedMessage();



};


#endif //VIRUS_SPREADING_MODEL_MPIHANDLER_H
