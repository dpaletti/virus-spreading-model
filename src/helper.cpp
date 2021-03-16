#include <utility>
#include <cmath>
#include <mpi.h>
#include <algorithm>
#include "InputParser.h"
#include "Cell.h"
#include "Infected.h"
#include "Individual.h"
#include "World.h"

// TODO: move all methods except serialize and deserialize to a coordination (think of a better name) class
// TODO: move serialize and deserialize to a helper file (no state)

int split_individuals(int my_rank, InputParser *inputParser, int world_size) {

    int accumulator;
    int individuals = std::floor(inputParser->getIndividualsNumber() / world_size);
    if (my_rank == 0) {
        MPI_Send(&individuals, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&accumulator, 1, MPI_INT, world_size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        individuals += inputParser->getIndividualsNumber() - accumulator;
    } else {
        int destination = my_rank + 1;
        MPI_Recv(&accumulator, 1, MPI_INT, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        accumulator += individuals;
        if (my_rank == world_size)
            destination = 0;
        MPI_Send(&accumulator, 1, MPI_INT, destination, 0, MPI_COMM_WORLD);
    }
    return individuals;

}

rapidjson::StringBuffer serialize_list(const std::vector<Infected>& infected_list){
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    writer.StartArray();
    for (const auto &item : infected_list) {
        item.Serialize(writer);
    }
    writer.EndArray();
   return sb;

}
std::string spread_infected(int my_rank, int world_size, rapidjson::StringBuffer& serialized, std::vector<Infected> infected_list) {
    std::string buf;
    MPI_Status status;
    int messageSize;
    rapidjson::Document document;
    if (my_rank == 0) {
        MPI_Send(serialized.GetString(), serialized.GetSize(), MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
        MPI_Probe(world_size - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &messageSize);
        MPI_Recv(&buf, messageSize, MPI_CHAR, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Probe(my_rank - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_CHAR, &messageSize);
        MPI_Recv(&buf, messageSize, MPI_CHAR, my_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        document.Parse(buf.c_str());
        for (rapidjson::Value::ConstMemberIterator iterator = document.MemberBegin();
             iterator != document.MemberEnd(); ++iterator) {
            auto *temp_infected = new Infected();
            temp_infected->Deserialize(iterator->value);
            infected_list.push_back(*temp_infected);
        }
        serialized = serialize_list(infected_list);
        MPI_Send((void *) serialized.GetString(), serialized.GetSize(), MPI_CHAR, my_rank + 1, 0, MPI_COMM_WORLD);
    }
    return buf;
}

void broadcast_global_infected(int my_rank, std::string current_serialized_infected){
    MPI_Status status;
    int messageSize;
    if(my_rank == 0){
        MPI_Bcast(&current_serialized_infected,current_serialized_infected.size(),MPI_CHAR,0,MPI_COMM_WORLD);
    }else{
        MPI_Probe(0,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status,MPI_CHAR,&messageSize);
        MPI_Bcast(&current_serialized_infected,messageSize,MPI_CHAR,0,MPI_COMM_WORLD);
    }
}

std::vector<Infected> deserialize_list(const std::string& current_serialized_infected){
    std::vector<Infected> infected_list;
    rapidjson::Document document;

    document.Parse(current_serialized_infected.c_str());
    for (rapidjson::Value :: ConstMemberIterator iterator = document.MemberBegin(); iterator != document.MemberEnd();++iterator) {
        auto *temp_infected = new Infected();
        temp_infected->Deserialize(iterator->value);
        infected_list.push_back(*temp_infected);
    }
    return infected_list;

}

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
void spread_virus (World world, std::vector<Infected> infected_list){
    std::vector<Infected> current_intersection;
    std::vector<Infected> current_difference;
    std::pair<std::vector<Infected>, std::vector<Infected>> intersection_and_difference;
    Point curr_position;
    bool transmission = false;

    for (Individual individual : world.getIndividuals()) {
        curr_position = individual.getPosition();
        intersection_and_difference = individual.getIntersectionAndDifference(infected_list);
        current_intersection = intersection_and_difference.first;
        current_difference = intersection_and_difference.second;

        transmission = update_contacts_intersection(&individual, current_intersection, world);
        transmission = update_contacts_difference(transmission, &individual, current_difference, world);
        //moving

        individual.update(transmission, world.getTimeStep());
    }
}

