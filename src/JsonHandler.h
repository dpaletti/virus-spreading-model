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
/**
 * Used to handle serialization and deserialization of messages. Leverages the rapidJson library.
 */
class JsonHandler {
public:

    void serialize_infected_list(const std::vector<Infected>& infected_list);

    JsonHandler();

    std::vector<Infected> deserialize_infected_list(char* received_message);
    std::string getSerialized() const;
    /**
     * Used to serialize the statistics of each country: name, immune count,infected count and susceptible count
     * @param countries Vector of the countries to serialize the stats from
     */
    void serialize_stats(const std::vector<Country>& countries);
    /**
     * Used to add to the infected list of a world representation, the infected list received from another world
     * representation
     * @param received_message Message containing the infected list from another world representation
     * @param world World representation to accumulate infected in
     */
    void accumulate_infected(char* received_message, World *world);
    /**
     * Used to add the stats received from another world representation to the world received as a parameter
     * @param received_message Message containing the stats from another world representation
     * @param world World representation to accumulate stats in
     */
    void accumulate_stats(char* received_message, World *world);
    /**
     * Used to parse the message into the document attribute
     * @param received_message
     */
    void parse(char* received_message);
    /**
     * Used to update the stats of the world upon receiving the complete count.
     * @param received_message Contains the complete count of the stats between all world representation
     * @param world World representation to which stats are updated
     */
    void update_stats(char* received_message, World *world);


private:
    rapidjson::Document document;
    std::string serialized_string;

};


#endif //VIRUS_SPREADING_MODEL_JSONHANDLER_H
