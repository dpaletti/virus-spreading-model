//
// Created by chiar on 20/03/2021.
//

#ifndef VIRUS_SPREADING_MODEL_JSONHANDLER_H
#define VIRUS_SPREADING_MODEL_JSONHANDLER_H


#include <rapidjson/stringbuffer.h>
#include "Infected.h"
#include "Country.h"
#include "World.h"

class World;

class JsonHandler {
public:
    void serialize_infected_list(const std::vector<Infected>& infected_list);

    JsonHandler();

    std::vector<Infected> deserialize_infected_list(char* received_message);
    std::string getSerialized() const;
    void serialize_stats(const std::vector<Country>& countries);
    void accumulate_infected(char* received_message, World *world);
    void accumulate_stats(char* received_message, World *world);
    void parse(char* received_message);
    void update_stats(char* received_message, World *world);


private:
    rapidjson::Document document;
    std::string serialized_string;

};


#endif //VIRUS_SPREADING_MODEL_JSONHANDLER_H
