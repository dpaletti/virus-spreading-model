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

    JsonHandler jsonHandler = JsonHandler();
    // Infected list

    for(int step = 0; step < world.getDayLength(); step++){
        world.updatePositions();

        world.buildInfectedList();

        jsonHandler.serialize_infected_list(world.getInfectedList());

        mpiHandler.ring(jsonHandler, &world, &JsonHandler::accumulate_infected);

        mpiHandler.broadcast();

        world.setInfectedList(jsonHandler.deserialize_infected_list(mpiHandler.getReceivedMessage()));

        world.spread_virus();
    }

    world.computeStats();
    jsonHandler.serialize_stats(world.getCountries());

    mpiHandler.ring(jsonHandler, &world, &JsonHandler::accumulate_stats);
    mpiHandler.broadcast();

    jsonHandler.update_stats(mpiHandler.getReceivedMessage(), &world);
    world.printStats();



    MPI_Finalize();
}