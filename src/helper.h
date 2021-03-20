#include <utility>
#include <cmath>
#include <mpi.h>
#include <algorithm>
#include "InputParser.h"
#include "Cell.h"
#include "Infected.h"
#include "Individual.h"
#include "World.h"

#ifndef VIRUS_SPREADING_MODEL_HELPER_H
#define VIRUS_SPREADING_MODEL_HELPER_H

#endif //VIRUS_SPREADING_MODEL_HELPER_H

bool update_contacts_intersection(Individual *individual, std::vector<Infected> current_intersection, World world);
bool update_contacts_difference(bool transmission, Individual *individual, std::vector<Infected> current_difference, World world);
void spread_virus (World world, const std::vector<Infected>& infected_list);

