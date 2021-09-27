#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cmath>
#include "World.h"
#include "Grid.h"
#include "InputParser.h"
#include "MpiHandler.h"


float World::getLength() const {
    return length;
}

float World::getWidth() const {
    return width;
}



void World::place_countries(int my_rank) {
    int number_of_countries = getCountries().size();
    Grid grid = Grid(number_of_countries, getLength(), getWidth());
    Country* current_country;
    for(int i = 0; i < number_of_countries; i++){
        current_country = (Country*) &countries[i];
        try {
            //printf("\n\n\n\nTrying to place country number %d, with width %f and length %f , number of countries is: %d",i,current_country->getWidth(),current_country->getLength(),number_of_countries);
            current_country->setAnchorPoint(grid.place_country(*current_country));
        } catch (const std::runtime_error& e){
            if (my_rank == 0)
                std::cout << "Country " << current_country->getName() << " does not fit into the given world, not placed." << std::endl;
            countries.erase(countries.begin() + i);
            i--;
            number_of_countries--;
        }
    }
}

World::World(InputParser &inputParser, MpiHandler &mpiHandler) :
    days(inputParser.getDays()),
    length(inputParser.getWorldSize().second),
    width(inputParser.getWorldSize().first),
    countries(std::move(Country::buildCountries(inputParser.getCountries()))),
    velocity(inputParser.getVelocity()),
    maximumSpreadingDistance(inputParser.getMaximumSpreadingDistance()),
    timeStep(inputParser.getTimeStep()){
    place_countries(mpiHandler.getMyRank());
    day_length = std::floor(86400 / inputParser.getTimeStep());
    addIndividuals(mpiHandler.split_individuals(inputParser), std::floor(inputParser.getInfectedNumber() / mpiHandler.getWorldSize()), mpiHandler.getMyRank());
}

const std::vector<Country> &World::getCountries() const {
    return countries;
}

void World::printWorld() {
    std::cout << "This world has a length of " << length << " and a width of " << width << "." << std::endl;
    std::cout << "It contains the following countries: " << std::endl;
    for (auto &country : countries) {
        std::cout << "Country " << country.getName() << " has length of " << country.getLength() << " and a width of " << country.getWidth() << " is anchored in " << country.getAnchorPoint().toString() << std::endl;
    }
    for (const auto &individual : individuals) {
        std::cout << "Individual " << individual.getId() << " on " << individual.getPosition().toString();
    }

}

void World::addIndividuals(int number_of_individuals, int number_of_infected, int rank) {
    for (int i = 0; i < number_of_individuals; i++){
        individuals.emplace_back(i <= number_of_infected, length, width, std::to_string(rank) + "-" + std::to_string(i));
    }
}

void World::updatePositions() {
    float x, y;
    for (auto & individual : individuals){
        x = individual.getPosition().getX() + velocity * timeStep * individual.getDirection().getX();
        y = individual.getPosition().getY() + velocity * timeStep * individual.getDirection().getY();
        if (x > length || y > width || x < 0 || y < 0){
            individual.relocate(length, width);
            continue;
        }
        individual.setPosition(Point(x, y));
    }
}

std::vector<Individual> &World::getIndividuals(){
    return individuals;
}

float World::getMaximumSpreadingDistance() const {
    return maximumSpreadingDistance;
}

float World::getTimeStep() const {
    return timeStep;
}

int World::getSusceptibleToInfected() {
    return susceptible_to_infected;
}

int World::getInfectedToImmune() {
    return infected_to_immune;
}

int World::getImmuneToSusceptible() {
    return immune_to_susceptible;
}

bool World::update_contacts_intersection(Individual *individual, std::vector<Infected> current_intersection) const{
    float distance;
    bool transmission = false;
    Point curr_position = individual->getPosition();


    for (Contact contact : individual->getRecentContacts()) {
        auto curr_infected = std::find(current_intersection.begin(), current_intersection.end(), contact);
        if (curr_infected != current_intersection.end()){
            distance = curr_position.getDistance(curr_infected.base()->getPosition());
            if (distance <= getMaximumSpreadingDistance()){
                contact.setContactTime(contact.getContactTime() + getTimeStep());
                if (contact.getContactTime() >= getSusceptibleToInfected())
                    transmission = true;
            } else {
                individual->removeContact(contact.getId());
            }
        }
    }
    return transmission;
}

bool World::update_contacts_difference(bool transmission, Individual *individual, const std::vector<Infected>& current_difference) const{
    float distance;
    Point curr_position = individual->getPosition();
    for (const auto &inf : current_difference) {
        distance = curr_position.getDistance(inf.getPosition());
        if (distance <= getMaximumSpreadingDistance()){
            individual->addContact(inf.getId(), getTimeStep());
            transmission = true;
        }
    }
    return transmission;
}

void World::spread_virus (){
    std::vector<Infected> current_intersection;
    std::vector<Infected> current_difference;
    std::pair<std::vector<Infected>, std::vector<Infected>> intersection_and_difference;
    bool transmission;

    for (Individual &individual : getIndividuals()) {
        intersection_and_difference = individual.getIntersectionAndDifference(infected_list);
        current_intersection = intersection_and_difference.first;
        current_difference = intersection_and_difference.second;

        transmission = update_contacts_intersection(&individual, current_intersection);
        transmission = update_contacts_difference(transmission, &individual, current_difference);

        individual.update(transmission, getTimeStep());
    }
}

int World::getDayLength() const {
    return day_length;
}

int World::getIndividualsNumber() {
   return individuals.size();
}

void World::buildInfectedList() {
    Individual current_individual;
    infected_list.clear();
    for (int i = 0; i < getIndividualsNumber(); i++){
        current_individual = getIndividuals()[i];
        if (current_individual.infected()){
            infected_list.emplace_back(current_individual.getPosition(), current_individual.getId());
        }
    }

}

std::vector<Infected> &World::getInfectedList() {
    return infected_list;
}

void World::setInfectedList(const std::vector<Infected> &infectedList) {
    infected_list = infectedList;
}

Country* World::findCountry(Individual &individual){
    Point point = individual.getPosition();
    Point anchor_point;
    for (auto &country : countries) {
        anchor_point = country.getAnchorPoint();
        if (point.getX() >= anchor_point.getX() && point.getX() <= anchor_point.getX() + country.getLength()){
            if (point.getY() >= anchor_point.getY() && point.getY() <= anchor_point.getY() + country.getWidth())
                return &country;
        }
    }
    std:: string state;
    if (individual.immune())
        state="immune";
    else if (individual.infected())
        state="infected";
    else if (!individual.infected() && !individual.immune())
        state="susceptible";
    std::string error = "\nIndividual " + individual.getId() + " is " + state + " and does not belong to any country\n";
    throw std::runtime_error(error);
}

void World::computeStats() {
    Country* country;
    for (auto &individual : individuals) {
        try{
            country = findCountry(individual);
        } catch (const std::runtime_error& e){
            std::cout << e.what() << std::endl;
            continue; //individual does not belong to any country
        }
        if (individual.immune())
            country->updateImmuneCount();
        else if (individual.infected())
            country->updateInfectedCount();
        else if (!individual.infected() && !individual.immune())
            country->updateSusceptibleCount();
    }
}

Country *World::findCountryByName(const std::string& country_name) {
    for (auto &country : countries) {
        if(country.getName() == country_name)
            return &country;
    }
    std::string error_message = "Could not find country with name " + country_name;
    throw std::runtime_error(error_message);
}

void World::printStats() {
    for (auto &c : countries)
        c.printStats();
}

int World::getDays() const {
    return days;
}

void World::reset_stats() {
    for (auto &country : countries)
        country.resetCounters();

}


