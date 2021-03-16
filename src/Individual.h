//
// Created by dpaletti on 2021-03-14.
//

#ifndef VIRUS_SPREADING_MODEL_INDIVIDUAL_H
#define VIRUS_SPREADING_MODEL_INDIVIDUAL_H


#include <utility>
#include <vector>
#include "Point.h"
#include "Contact.h"
#include "Infected.h"

class Individual {
private:
public:
    Individual(bool isInfected, float bound_x, float bound_y, std::string);

private:
    Point direction;
    bool isInfected{};
    std::string id;
    std::vector<Contact> recent_contacts;
    Point position;
    float timer;

public:
    void setPosition(const Point &point);

    const std::string &getId() const;

private:
public:
    Individual();

private:
    bool isImmune{};
    void randomize_position(float bound_x, float bound_y);

public:
    const Point &getDirection() const;
    bool isInfected1() const;
    bool isImmune1() const;
    const Point &getPosition() const;
    void relocate(float bound_x, float bound_y);
    Contact* findContactById(std :: string basicString);
    void addContact(const std :: string& basicString, float timeStep);
    void removeContact(std :: string idToRemove);
    std::pair<std::vector<Infected>, std::vector<Infected>> getIntersectionAndDifference(std::vector<Infected> globalInfected);
    bool operator<(const Individual &i){
        return id < i.getId();
    }
    bool operator<(const Contact &c){
        return id < c.getId();
    }
    const std::vector<Contact> &getRecentContacts() const;
    void update(bool transmission);
};


#endif //VIRUS_SPREADING_MODEL_INDIVIDUAL_H
