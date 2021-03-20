#include<iostream>
#include <mpi.h>
#include <vector>
#include <cmath>
#include "InputParser.h"
#include "Country.h"
#include "World.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "Infected.h"
#include "helper.h"
#include "MpiHandler.h"
#include "JsonHandler.h"

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(nullptr, nullptr);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Parse input json
    InputParser inputParser = InputParser("../config/input.json");

    // Initialize World and place countries
    std::vector<Country> countries = Country::buildCountries(inputParser.getCountries());
    std::pair<float, float> worldSize = inputParser.getWorldSize();
    World world = World(worldSize.second, worldSize.first, countries, inputParser.getVelocity(), inputParser.getMaximumSpreadingDistance(), inputParser.getTimeStep());
    MpiHandler mpiHandler = MpiHandler(my_rank, world_size);
    JsonHandler jsonHandler = JsonHandler();
    world.printWorld();

    MPI_Barrier(MPI_COMM_WORLD);

    // Initialize number of infected
    int infected = std::floor(inputParser.getInfectedNumber() / world_size);

    // Initialize day length
    int day_length = std::floor(86400 / inputParser.getTimeStep());

    // Split individuals among processes
    int individuals = mpiHandler.split_individuals(&inputParser);
    world.addIndividuals(individuals, infected, my_rank);

    MPI_Barrier(MPI_COMM_WORLD);

    // Infected list
    std::vector<Infected> infected_list;

    // Serialization helper variables
    rapidjson::StringBuffer serialized;


    // Day loop
    Individual current_individual;
    for(int step = 0; step < day_length; step+=step){
        world.updatePositions();

        // Build infected list
        for (int i = 0; i < individuals; i++){
            current_individual = world.getIndividuals()[i];
            if (current_individual.isInfected1()){
                infected_list.emplace_back(current_individual.getPosition(), current_individual.getId());
            }
        }

        // Serialize infected list
        jsonHandler.serialize_list(infected_list);

        // Gather current infected from all processes
        mpiHandler.spread_infected(jsonHandler, infected_list);

        MPI_Barrier(MPI_COMM_WORLD);

        // Send all infected to all processes
        mpiHandler.broadcast_global_infected();
        printf("\n\nMAIN -> RANK: %d, STEP %d\n\n", my_rank, step);

        // Deserialize received infected list
        infected_list = jsonHandler.deserialize_list(mpiHandler.getCurrentSerializedInfected());

        spread_virus(world, infected_list);
    }

    MPI_Finalize();
}