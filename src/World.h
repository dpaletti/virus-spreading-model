#ifndef VIRUS_SPREADING_MODEL_WORLD_H
#define VIRUS_SPREADING_MODEL_WORLD_H

#include <list>
#include <vector>
#include "Country.h"
#include "Grid.h"
#include "Individual.h"
#include "InputParser.h"
#include "MpiHandler.h"

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

    void place_countries();

    const std::vector<Individual> &getIndividuals() const;

    void printWorld();

    void addIndividuals(int number_of_individuals, int number_of_infected, int rank);

    void updatePositions();

    float getMaximumSpreadingDistance() const;

    float getTimeStep() const;

    void spread_virus();

    void buildInfectedList();

    const std::vector<Infected> &getInfectedList() const;

    void setInfectedList(const std::vector<Infected> &infectedList);

    int getIndividualsNumber();

    static int getSusceptibleToInfected();

    static int getInfectedToImmune();

    static int getImmuneToSusceptible();

    int getDayLength() const;

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
