#ifndef VIRUS_SPREADING_MODEL_WORLD_H
#define VIRUS_SPREADING_MODEL_WORLD_H

#include <list>
#include <vector>
#include "Country.h"
#include "Grid.h"
#include "Individual.h"
#include "InputParser.h"
#include "MpiHandler.h"

class MpiHandler;
/**
 * Used to represent the world. Has the information about geographical and physical quantities, as well as
 * virus properties and list of infected, individuals and countries.
 */
class World {
private:
    bool update_contacts_intersection(Individual *individual, std::vector<Infected> current_intersection) const;

    bool update_contacts_difference(bool transmission, Individual *individual,
                                    const std::vector<Infected> &current_difference) const;

    float velocity;
    float maximumSpreadingDistance;
    float timeStep;
    float length, width;
    std::vector<Infected> infected_list;

    static const int susceptible_to_infected = 600;

    static const int infected_to_immune = 864000; //10 days
    static const int immune_to_susceptible = 7776000; //3 months

    int day_length;

    std::vector<Individual> individuals;
    std::vector<Country> countries;

public:
    World(InputParser &inputParser, MpiHandler &mpiHandler);

    const std::vector<Country> &getCountries() const;

    float getLength() const;

    float getWidth() const;

    /**
     * Used to place the countries received in input into the world
     * @param my_rank Rank of the calling process
     */
    void place_countries(int my_rank);

    const std::vector<Individual> &getIndividuals() const;

    void printWorld();

    void addIndividuals(int number_of_individuals, int number_of_infected, int rank);

    /**
     * Used to update the positions of the individuals in the world at each timestep
     */
    void updatePositions();

    float getMaximumSpreadingDistance() const;

    float getTimeStep() const;

    /**
     * Used to spread the virus at each timestep between the individuals of the world.
     */
    void spread_virus();

    void buildInfectedList();

    std::vector<Infected> &getInfectedList();

    void setInfectedList(const std::vector<Infected> &infectedList);

    int getIndividualsNumber();

    static int getSusceptibleToInfected();

    static int getInfectedToImmune();

    /**
     * Used to find the country where an individual is in
     * @param individual individual to search the country for
     * @return The searched country
     */
    Country *findCountry(Individual &individual);

    void computeStats();

    static int getImmuneToSusceptible();

    int getDayLength() const;

    /**
     * Used to find a country by name
     * @param country_name
     * @return
     */
    Country *findCountryByName(const std::string& country_name);
    /**
     * Used to print to screen all the relevant stats for each country: country name, immune count, susceptible count, infected count.
     */
    void printStats();

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
