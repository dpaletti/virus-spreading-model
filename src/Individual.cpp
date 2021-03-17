#include "Individual.h"
#include "Infected.h"
#include "World.h"
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

/**Contact* Individual::findContactById(std :: string basicString) {
    auto iterator = std :: find_if(recent_contacts.begin(),recent_contacts.end(),
                                   [&](const std::pair<std::string, float>& cont) { return (cont.first == basicString);});
    if(iterator != recent_contacts.end())
        return iterator.base();
    else
        return nullptr;
}**/

void Individual::addContact(const std::string& basicString, float timeStep) {
    recent_contacts.emplace_back(basicString, timeStep);
}

void Individual::removeContact(std::string idToRemove) {
    recent_contacts.erase(std::remove_if(recent_contacts.begin(),recent_contacts.end(),
                                              [&](const Contact& cont) { return (cont.getId() == idToRemove);}), recent_contacts.end());
}

struct InfectedContactComparator
{
    bool operator()(const Infected& p_left, const Contact& p_right)
    {
        return p_left.getId() < p_right.getId();
    }
    bool operator()(const Contact& p_left, const Infected& p_right)
    {
        return p_left.getId() < p_right.getId();
    }
};

std::pair<std::vector<Infected>, std::vector<Infected>> Individual::getIntersectionAndDifference(std::vector<Infected> globalInfected) {
    std::vector<Infected> intersection;
    std::vector<Infected> difference;
    std::sort(recent_contacts.begin(),recent_contacts.end());
    std::sort(globalInfected.begin(), globalInfected.end());
    std::set_intersection(globalInfected.begin(), globalInfected.end(), recent_contacts.begin(), recent_contacts.end(), inserter(intersection, intersection.begin()), InfectedContactComparator{});
    std::set_difference(globalInfected.begin(), globalInfected.end(), recent_contacts.begin(), recent_contacts.end(), inserter(difference, difference.begin()), InfectedContactComparator{});

    return {intersection, difference};
}

const std::vector<Contact> &Individual::getRecentContacts() const {
    return recent_contacts;
}

void Individual::update(bool transmission, float timeStep) {
    timer += timeStep;
    if (isInfected && timer >= (float)World::getInfectedToImmune()){ //no longer infected, becomes immune
        isImmune = true;
        isInfected = false;
        timer = 0;
        return;
    }

    if (isImmune && timer >= (float)World::getImmuneToSusceptible()){ //no longer immune
        isImmune = false;
        if (transmission) //becomes infected
            isInfected = true;
        timer = 0;
        return;
    }

    if (!isImmune && !isInfected){ //susceptible
        if (transmission){ //becomes infected
            isInfected = true;
            timer = 0;
        }
    }
}
