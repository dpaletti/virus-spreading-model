//
// Created by dpaletti on 2021-03-09.
//

#include "World.h"
#include "Cell.h"
#include "Grid.h"



float World::getLength() const {
    return length;
}

float World::getWidth() const {
    return width;
}



void World::place_countries() const{
    int number_of_countries = getCountries().size();
    Grid grid = Grid(number_of_countries, getLength(), getWidth());
    for(int i = 0; i < number_of_countries; i++){
        Country current_country = countries[i];
        current_country.setAnchorPoint(grid.place_country(current_country));
    }
}

World::World(float length, float width, const std::vector<Country> &countries) : length(length), width(width),
                                                                                 countries(countries) {}

const std::vector<Country> &World::getCountries() const {
    return countries;
}



