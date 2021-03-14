#include<iostream>
#include <mpi.h>
#include <vector>
#include "InputParser.h"
#include "Country.h"
#include "World.h"

int main(int argc, char** argv) {
    /**
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello World message
    printf("Hello World from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
    **/
    InputParser inputParser = InputParser("../config/input.json");
    std::vector<Country> countries = Country::buildCountries(inputParser.getCountries());
    std::pair<float, float> world_size = inputParser.getWorldSize();
    World world = World(world_size.second, world_size.first, countries, inputParser.getVelocity(), inputParser.getMaximumSpreadingDistance(), inputParser.getTimeStep());
    world.printWorld();
}