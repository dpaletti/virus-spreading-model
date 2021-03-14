#ifndef VIRUS_SPREADING_MODEL_WORLD_H
#define VIRUS_SPREADING_MODEL_WORLD_H

#include <list>
#include <vector>
#include "Country.h"
#include "Grid.h"

class World {
public:
    const std::vector<Country> &getCountries() const;

public:
    World(float length, float width, std::vector<Country> countries, float velocity, float maximumSpreadingDistance, float timeStep);

    float getLength() const;

    float getWidth() const;


    void place_countries();

    void printWorld();

private:
    float velocity;
    float maximumSpreadingDistance;
    float timeStep;
    float length, width;
    std::vector<Country> countries;

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
