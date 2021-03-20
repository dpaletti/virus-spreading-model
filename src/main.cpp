#include<iostream>
#include <mpi.h>
#include "InputParser.h"
#include "World.h"
#include "MpiHandler.h"
#include "JsonHandler.h"

int main(int argc, char** argv) {

    MPI_Init(nullptr, nullptr);

    int mpiWorldSize;
    MPI_Comm_size(MPI_COMM_WORLD, &mpiWorldSize);

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MpiHandler mpiHandler = MpiHandler(my_rank, mpiWorldSize);
    InputParser inputParser = InputParser("../config/input.json");
    World world = World(inputParser, mpiHandler);

    world.printWorld();

    JsonHandler jsonHandler = JsonHandler();
    // Infected list

    for(int step = 0; step < world.getDayLength(); step++){
        world.updatePositions();

        world.buildInfectedList();

        jsonHandler.serialize_list(world.getInfectedList());

        mpiHandler.spread_infected(jsonHandler, world.getInfectedList());

        printf("\nRANK %d at step %d\n", my_rank, step);

        mpiHandler.broadcast_global_infected();

        world.setInfectedList(jsonHandler.deserialize_list(mpiHandler.getCurrentSerializedInfected()));

        world.spread_virus();
    }

    world.computeStats();

    MPI_Finalize();
}