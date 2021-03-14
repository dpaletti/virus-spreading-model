//
// Created by dpaletti on 2021-03-14.
//

#ifndef VIRUS_SPREADING_MODEL_INDIVIDUAL_H
#define VIRUS_SPREADING_MODEL_INDIVIDUAL_H


#include <utility>
#include <vector>
#include "Point.h"

class Individual {
private:
public:
    Individual(bool isInfected, float bound_x, float bound_y, std::string);

private:
    Point direction;
    bool isInfected;
    std::string id;
    std::vector<std::pair<std::string, float>> recent_contacts;
public:
    void setPosition(const Point &position);

    const std::string &getId() const;

private:
public:
    Individual();

private:
    bool isImmune;
    void randomize_position(float bound_x, float bound_y);

public:
    const Point &getDirection() const;
    bool isInfected1() const;
    bool isImmune1() const;
    const Point &getPosition() const;
    void relocate(float bound_x, float bound_y);

private:
    Point position;

};


#endif //VIRUS_SPREADING_MODEL_INDIVIDUAL_H
