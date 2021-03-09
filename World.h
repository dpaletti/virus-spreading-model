//
// Created by dpaletti on 2021-03-09.
//

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
    World(float length, float width, const std::vector<Country> &countries);

    float getLength() const;

    float getWidth() const;


    void place_countries() const;

private:
    float length, width;
    std :: vector<Country> countries;
    void place_country(Country country, Grid grid) const;

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
