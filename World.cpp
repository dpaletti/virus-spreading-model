//
// Created by dpaletti on 2021-03-09.
//

#include "World.h"
#include "Cell.h"
#include "Grid.h"

World::World(float length, float width, const std::list<Country> &countries) : length(length), width(width),
                                                                               countries(countries) {}

float World::getLength() const {
    return length;
}

float World::getWidth() const {
    return width;
}

const std::list<Country> &World::getCountries() const {
    return countries;
}

void World::set_countries_anchor_point() const{
    int number_of_countries = getCountries().size();
    Grid grid = Grid(number_of_countries, getLength(), getWidth());

}

void World::place_country(Country country, Grid grid) const {
    for(int i=0; i<grid.getNumberOfActiveRows(); i++){
        for(int j=0; j<grid.getNumberOfActiveColumns(); j++){
            if(country.getWidth() <= grid.getCells()[i][j].getWidth() && country.getLength() <= grid.getCells()[i][j].getLength()){
                // country fits in exactly one cell
            }
            else if(country.getWidth() > grid.getCells()[i][j].getWidth() && country.getLength() <= grid.getCells()[i][j].getLength()){
                // country fits length-wise but not width-wise
            }
            else if(country.getWidth() <= grid.getCells()[i][j].getWidth() && country.getLength() > grid.getCells()[i][j].getLength()){
                // country fits width-wise but not length wise
            }
            else{

            }
        }
    }
}
