#include<iostream>
#include <mpi.h>
#include <vector>
#include <chrono>
#include <cmath>
#include "InputParser.h"
#include "Country.h"
#include "World.h"

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    InputParser inputParser = InputParser("../config/input.json");
    std::vector<Country> countries = Country::buildCountries(inputParser.getCountries());
    std::pair<float, float> worldSize = inputParser.getWorldSize();
    World world = World(worldSize.second, worldSize.first, countries, inputParser.getVelocity(), inputParser.getMaximumSpreadingDistance(), inputParser.getTimeStep());
    world.printWorld(); //debug

    MPI_Barrier(MPI_COMM_WORLD);

    int infected = std::floor(inputParser.getInfectedNumber() / world_size);
    int individuals = std::floor(inputParser.getIndividualsNumber() / world_size);
    int accumulator;

    if (my_rank == 0){
        MPI_Send(&individuals, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&accumulator, 1, MPI_INT, world_size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        individuals += inputParser.getIndividualsNumber() - accumulator;
    } else {
        int destination = my_rank + 1;
        MPI_Recv(&accumulator, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        accumulator += individuals;
        if (my_rank == world_size)
            destination = 0;
        MPI_Send(&accumulator, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    }

    world.addIndividuals(individuals, infected, my_rank);

    int day_length = std::floor(86400 / inputParser.getTimeStep());
    MPI_Barrier(MPI_COMM_WORLD);
    std::vector<std::pair<std::string, Point>> list_of_infected;
    Individual current_individual;

    for(int step = 0; step < day_length; step++){
        world.updatePositions();
        for (int i = 0; i < individuals; i++){
            current_individual = world.getIndividuals()[i];
            if (current_individual.isInfected1()){
                list_of_infected.emplace_back(current_individual.getId(), current_individual.getPosition());
            }
        }
        //list of infected needs to be serialized
        //MPI_Bcast(&list_of_infected, //size of the string we just created, char, ... );
    }

    MPI_Finalize();
}