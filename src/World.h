#ifndef VIRUS_SPREADING_MODEL_WORLD_H
#define VIRUS_SPREADING_MODEL_WORLD_H

#include <list>
#include <vector>
#include "Country.h"
#include "Grid.h"
#include "Individual.h"

class World {
public:
    const std::vector<Country> &getCountries() const;

public:
    World(float length, float width, std::vector<Country> countries, float velocity, float maximumSpreadingDistance, float timeStep);

    float getLength() const;

    float getWidth() const;

    void place_countries();

    const std::vector<Individual> &getIndividuals() const;

    void printWorld();

    void addIndividuals(int number_of_individuals, int number_of_infected, int rank);

    void updatePositions();

private:
    float velocity;
    float maximumSpreadingDistance;
    float timeStep;
    float length, width;

    //seconds
    const int susceptible_to_infected = 600; //10 minutes
    const int infected_to_immune = 864000; //10 days
    const int immune_to_susceptible = 7776000; //3 months

    std::vector<Individual> individuals;
    std::vector<Country> countries;

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
