#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>
#include "World.h"
#include "Grid.h"



float World::getLength() const {
    return length;
}

float World::getWidth() const {
    return width;
}



void World::place_countries() {
    int number_of_countries = getCountries().size();
    Grid grid = Grid(number_of_countries, getLength(), getWidth());
    Country* current_country;
    for(int i = 0; i < number_of_countries; i++){
        current_country = (Country*) &countries[i];
        try {
            current_country->setAnchorPoint(grid.place_country(*current_country));
        } catch (const std::runtime_error& e){
            std::cout << "Country " << current_country->getName() << " skipping placement." << std::endl;
            countries.erase(countries.begin() + i);
            i--;
            number_of_countries--;
        }
    }
}

World::World(float length, float width, std::vector<Country> countries, float velocity, float maximumSpreadingDistance, float timeStep) : length(length), width(width),
                                                                                 countries(std::move(countries)), velocity(velocity), maximumSpreadingDistance(maximumSpreadingDistance), timeStep(timeStep) {place_countries();}

const std::vector<Country> &World::getCountries() const {
    return countries;
}

void World::printWorld() {
    std::cout << "This world has a length of " << length << " and a width of " << width << "." << std::endl;
    std::cout << "It contains the following countries: " << std::endl;
    for (auto &country : countries) {
        std::cout << "Country " << country.getName() << " has length of " << country.getLength() << " and a width of " << country.getWidth() << " is anchored in " << country.getAnchorPoint().toString() << std::endl;
    }

}

void World::addIndividuals(int number_of_individuals, int number_of_infected, int rank) {
    for (int i = 0; i < number_of_individuals; i++){
        individuals.emplace_back(i <= number_of_infected, length, width, std::to_string(rank) + "-" + std::to_string(i));
    }
}

void World::updatePositions() {
    float x, y;
    for (int i = 0; i < individuals.size(); i++){
        x = individuals[i].getPosition().getX() + velocity * timeStep * individuals[i].getDirection().getX();
        y = individuals[i].getPosition().getY() + velocity * timeStep * individuals[i].getDirection().getY();
        if (x > length || y > width){
            individuals[i].relocate(length, width);
            continue;
        }
        individuals[i].setPosition(Point(x, y));
    }
}

const std::vector<Individual> &World::getIndividuals() const {
    return individuals;
}

float World::getMaximumSpreadingDistance() const {
    return maximumSpreadingDistance;
}

float World::getTimeStep() const {
    return timeStep;
}



