//
// Created by dpaletti on 2021-03-14.
//

#include "Individual.h"
#include <random>
#include <algorithm>

Individual::Individual(bool isInfected, float bound_x, float bound_y, std::string id) : isInfected(isInfected), isImmune(false){
    randomize_position(bound_x, bound_y);
    id = id;
}

const Point &Individual::getDirection() const {
    return direction;
}

bool Individual::isInfected1() const {
    return isInfected;
}

bool Individual::isImmune1() const {
    return isImmune;
}

const Point &Individual::getPosition() const {
    return position;
}

void Individual::randomize_position(float bound_x, float bound_y) {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);
    std::uniform_real_distribution<double> distribution_bound_x(0, bound_x);
    std::uniform_real_distribution<double> distribution_bound_y(0, bound_y);

    position = Point(distribution_bound_x(generator), distribution_bound_y(generator));
    direction = Point (distribution(generator), distribution(generator));
}

void Individual::relocate(float bound_x, float bound_y) {
    randomize_position(bound_x, bound_y);
}

void Individual::setPosition(const Point &point) {
    Individual::position = point;
}

Individual::Individual() = default;

const std::string &Individual::getId() const {
    return id;
}

Contact* Individual::findContactById(std :: string basicString) {
    auto iterator = std :: find_if(recent_contacts.begin(),recent_contacts.end(),
                                   [&](const std::pair<std::string, float>& cont) { return (cont.first == basicString);});
    if(iterator != recent_contacts.end())
        return iterator.base();
    else
        return nullptr;
}

void Individual::addContact(const std::string& basicString, float timeStep) {
    recent_contacts.emplace_back(basicString, timeStep);
}

void Individual::removeContact(std::string basicString) {
    auto lastNotRemovedElement = std :: remove_if(recent_contacts.begin(),recent_contacts.end(),
                                                  [&](const std::pair<std::string, float>& cont) { return (cont.first == basicString);});

}

std::vector<Individual> Individual::getIntersection(std::vector<std::string> globalInfected) {
    std :: vector<Individual> out;
    std :: sort(recent_contacts.begin(),recent_contacts.end());
    std :: sort(globalInfected.begin(),globalInfected.end());
    std :: set_intersection(recent_contacts.begin(),recent_contacts.end(),globalInfected.begin(),globalInfected.end(),out);
    return out;
}


