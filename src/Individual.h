//
// Created by dpaletti on 2021-03-14.
//

#ifndef VIRUS_SPREADING_MODEL_INDIVIDUAL_H
#define VIRUS_SPREADING_MODEL_INDIVIDUAL_H


#include <utility>
#include <vector>
#include "Point.h"
#include "Contact.h"

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
    void removeContact(std :: string basicString);
    std :: vector<Individual> getIntersection(std :: vector<std ::string> globalInfected);
    bool operator<(const Individual &i){
        return id < i.getId();
    }
    bool operator<(const Contact &c){
        return id < c.getId();
    }

};


#endif //VIRUS_SPREADING_MODEL_INDIVIDUAL_H
