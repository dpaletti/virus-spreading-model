//
// Created by dpaletti on 2021-03-14.
//

#include "Individual.h"
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <random>
#include <cmath>

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

void Individual::setPosition(const Point &position) {
    Individual::position = position;
}

Individual::Individual() {}

const std::string &Individual::getId() const {
    return id;
}
