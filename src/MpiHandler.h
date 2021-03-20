
#ifndef VIRUS_SPREADING_MODEL_MPIHANDLER_H
#define VIRUS_SPREADING_MODEL_MPIHANDLER_H


#include <malloc.h>
#include "InputParser.h"
#include "Infected.h"
#include "JsonHandler.h"

class MpiHandler {
private:
    int my_rank;
    int world_size;
    int* individuals_split_accumulator = (int*)malloc(sizeof(int));
    int* message_size = (int*)malloc(sizeof(int));
    char* current_serialized_infected = nullptr;
public:
    int getMyRank() const;

    int getWorldSize() const;

    MpiHandler(int myRank, int worldSize);

    virtual ~MpiHandler();

    char* getCurrentSerializedInfected();
    int split_individuals(InputParser &inputParser);
    void spread_infected(JsonHandler &jsonHandler, std::vector<Infected> infected_list);
    void broadcast_global_infected();
private:
    void allocateInfected();



};


#endif //VIRUS_SPREADING_MODEL_MPIHANDLER_H
