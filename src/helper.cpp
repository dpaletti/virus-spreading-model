#include <utility>
#include <cmath>
#include <mpi.h>
#include <algorithm>
#include "helper.h"
#include "InputParser.h"
#include "Cell.h"
#include "Infected.h"
#include "Individual.h"
#include "World.h"

// TODO: move all methods except serialize and deserialize to a coordination (think of a better name) class

bool update_contacts_intersection(Individual *individual, std::vector<Infected> current_intersection, World world){
    float distance;
    bool transmission = false;
    Point curr_position = individual->getPosition();


    for (Contact contact : individual->getRecentContacts()) {
        auto curr_infected = std::find(current_intersection.begin(), current_intersection.end(), contact);
        if (curr_infected != current_intersection.end()){
            distance = curr_position.getDistance(curr_infected.base()->getPosition());
            if (distance <= world.getMaximumSpreadingDistance()){
                contact.setContactTime(contact.getContactTime() + world.getTimeStep());
                if (contact.getContactTime() >= world.getSusceptibleToInfected())
                    transmission = true;
            } else {
                individual->removeContact(contact.getId());
            }
        }
    }
    return transmission;
}

bool update_contacts_difference(bool transmission, Individual *individual, std::vector<Infected> current_difference, World world){
    float distance;
    Point curr_position = individual->getPosition();
    for (const auto &inf : current_difference) {
        distance = curr_position.getDistance(inf.getPosition());
        if (distance <= world.getMaximumSpreadingDistance()){
            individual->addContact(inf.getId(), world.getTimeStep());
            transmission = true;
        }
    }
    return transmission;
}
//updates the contact time and inserts new contacts in the recent contacts for each individual
void spread_virus (World world, const std::vector<Infected>& infected_list){
    std::vector<Infected> current_intersection;
    std::vector<Infected> current_difference;
    std::pair<std::vector<Infected>, std::vector<Infected>> intersection_and_difference;
    bool transmission = false;

    for (Individual individual : world.getIndividuals()) {
        intersection_and_difference = individual.getIntersectionAndDifference(infected_list);
        current_intersection = intersection_and_difference.first;
        current_difference = intersection_and_difference.second;

        transmission = update_contacts_intersection(&individual, current_intersection, world);
        transmission = update_contacts_difference(transmission, &individual, current_difference, world);

        individual.update(transmission, world.getTimeStep());
        printf("\n\nID: %s\n\n", individual.getId().c_str());
    }
}

