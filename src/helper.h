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

int split_individuals(int my_rank, InputParser *inputParser, int world_size);
std::string spread_infected(int my_rank, int world_size, rapidjson::StringBuffer& serialized, std::vector<Infected> infected_list);
rapidjson::StringBuffer serialize_list(const std::vector<Infected>& infected_list);
void broadcast_global_infected(int my_rank, std::string current_serialized_infected);
std::vector<Infected> deserialize_list(const std::string& current_serialized_infected);
bool update_contacts_intersection(Individual *individual, std::vector<Infected> current_intersection, World world);
bool update_contacts_difference(bool transmission, Individual *individual, std::vector<Infected> current_difference, World world);
void spread_virus (World world, std::vector<Infected> infected_list);

