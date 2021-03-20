//
// Created by chiar on 20/03/2021.
//

#ifndef VIRUS_SPREADING_MODEL_JSONHANDLER_H
#define VIRUS_SPREADING_MODEL_JSONHANDLER_H


#include <rapidjson/stringbuffer.h>
#include "Infected.h"

class JsonHandler {
public:
    void serialize_list(const std::vector<Infected>& infected_list);

    JsonHandler();

    std::vector<Infected> deserialize_list(const char* current_serialized_infected);
    const rapidjson::StringBuffer &getSerialized() const;


private:
    rapidjson::StringBuffer serialized;

};


#endif //VIRUS_SPREADING_MODEL_JSONHANDLER_H
