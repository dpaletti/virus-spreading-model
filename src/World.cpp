#include <stdexcept>
#include <iostream>
#include <utility>
#include "World.h"
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
        try {
            current_country.setAnchorPoint(grid.place_country(current_country));
        } catch (const std::runtime_error& e){
            std::cout << "Country " << current_country.getName() << " skipping placement." << std::endl;
        }
    }
}

World::World(float length, float width, std::vector<Country> countries) : length(length), width(width),
                                                                                 countries(std::move(countries)) {place_countries();}

const std::vector<Country> &World::getCountries() const {
    return countries;
}



