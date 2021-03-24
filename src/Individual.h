#ifndef VIRUS_SPREADING_MODEL_INDIVIDUAL_H
#define VIRUS_SPREADING_MODEL_INDIVIDUAL_H


#include <utility>
#include <vector>
#include "Point.h"
#include "Contact.h"
#include "Infected.h"
#include "Country.h"
/**
 * Represents an individual that is part of the world, keeps the information on its state regarding the virus,
 * its recent contacts, its position and its direction of movement.
 */
class Individual {
private:
    /**
     * Direction of movement specified by a point whose bound for x and y are (-1,1)
     */
    Point direction;
    bool isInfected{};
    std::string id;
    std::vector<Contact> recent_contacts;
    Point position;
    /**
     * Timer that keeps track of the time the individual has been infected,immune or susceptible, in seconds
     */
    float timer = 0;
    bool isImmune{};

public:
    /**
     * @param isInfected True to specify that the individual is infected from the start, false otherwise
     * @param bound_x Used to generate the individual random position on the x axis
     * @param bound_y Used to generate the individual random position on the y axis
     */
    Individual(bool isInfected, float bound_x, float bound_y, std::string);
    Individual();
    void setPosition(const Point &point);
    const std::string &getId() const;
    const Point &getDirection() const;
    bool infected() const;
    bool immune() const;
    const Point &getPosition() const;
    /**
     * Used to relocate the individual when it moves out of border
     * @param bound_x Used to generate the individual random position on the x axis
     * @param bound_y Used to generate the individual random position on the y axis
     */
    void relocate(float bound_x, float bound_y);
    /**
     * Used to add a contact to the contact vector
     * @param basicString Represents the id of the contact
     * @param timeStep Represents the time of the contact
     */
    void addContact(const std :: string& basicString, float timeStep);
    void removeContact(std :: string idToRemove);
    /**
     * Use to get the intersection and the difference sets between the vector of recentContacts and globalInfected
     * @param globalInfected It is the vector of infected individuals from all the world
     * @return Returns the intersection set as first of the pair and the difference set(globalInfected - RecentContacts) as second of the pair
     */
    std::pair<std::vector<Infected>, std::vector<Infected>> getIntersectionAndDifference(std::vector<Infected> globalInfected);
    bool operator<(const Individual &i){
        return id < i.getId();
    }
    bool operator<(const Contact &c){
        return id < c.getId();
    }
    const std::vector<Contact> &getRecentContacts() const;
    void update(bool transmission, float timeStep);
private:
    /**
     * Used to randomize the individual's position
     * @param bound_x Used to generate the individual random position on the x axis
     * @param bound_y Used to generate the individual random position on the y axis
     */
    void randomize_position(float bound_x, float bound_y);
};


#endif //VIRUS_SPREADING_MODEL_INDIVIDUAL_H
