#include<iostream>
#include <mpi.h>
#include <vector>
#include <chrono>
#include <cmath>
#include "InputParser.h"
#include "Country.h"
#include "World.h"
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "Infected.h"
#include "helper.cpp"

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
    world.printWorld(); // DEBUG

    MPI_Barrier(MPI_COMM_WORLD);

    // Initialize number of infected
    int infected = std::floor(inputParser.getInfectedNumber() / world_size);

    // Initialize day length
    int day_length = std::floor(86400 / inputParser.getTimeStep());

    // Split individuals among processes
    int individuals = split_individuals(my_rank, &inputParser, world_size);
    world.addIndividuals(individuals, infected, my_rank);

    MPI_Barrier(MPI_COMM_WORLD);

    // Infected list
    std::vector<Infected> infected_list;

    // Serialization helper variables
    rapidjson::StringBuffer serialized;
    std::string current_serialized_infected;


    // Day loop
    Individual current_individual;
    for(int step = 0; step < day_length; step++){
        world.updatePositions();

        // Build infected list
        for (int i = 0; i < individuals; i++){
            current_individual = world.getIndividuals()[i];
            if (current_individual.isInfected1()){
                infected_list.emplace_back(current_individual.getPosition(), current_individual.getId());
            }
        }

        // Serialize infected list
        serialized = serialize_list(infected_list);

        // Gather current infected from all processes
        current_serialized_infected = spread_infected(my_rank, world_size, serialized, infected_list);

        MPI_Barrier(MPI_COMM_WORLD);

        // Send all infected to all processes
        broadcast_global_infected(my_rank, current_serialized_infected);

        // Deserialize received infected list
        infected_list = deserialize_list(current_serialized_infected);

        // Compute new infected and update infection timers
        //For each individual of the world, i check the distance with the received infected individuals
        //If the distance is less than  the maximum spreading distance, then i check in the recent contacts of the individual
        //If it is in the recent contacts i update the time, otherwise i add it; i also add the individual to a temporary list
        //of the contacts happened during the last timestep, at the end of the loop, all recent contacts that are not also in the
        //temporary list will be removed
        float distance;
        std :: vector<std :: string> contactsInThisTimeStep;
        for (Individual individual : world.getIndividuals()) {
            Point curr_position = individual.getPosition();
            /*for (const auto &inf : infected_list) {
                // TODO compute new infections and update infection timers, update individuals state
                //Computing distance
                distance = curr_position.getDistance(inf.getPosition());
                if(distance <= world.getMaximumSpreadingDistance()){
                    auto contact = individual.findContactById(inf.getId());
                    if(contact != nullptr)
                        contact->second = contact->second + world.getTimeStep();
                    else
                        individual.addContact(inf.getId(),world.getTimeStep());
                    contactsInThisTimeStep.emplace_back(inf.getId());
                }
            }*/
            individual.getIntersection()
            //All the infected in the infected list are checked with the individual, now the contacts that do not belong in
            //the vector of contacts are removed from the contact list

        }
    }

    MPI_Finalize();
}