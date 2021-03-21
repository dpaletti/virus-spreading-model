#include "World.h"
#include <mpi.h>
#include "JsonHandler.h"

void JsonHandler::serialize_infected_list(const std::vector<Infected> &infected_list) {
    rapidjson::StringBuffer serialized;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(serialized);
    writer.StartObject();
    writer.Key("infected");
    writer.StartArray();
    for (const auto &item : infected_list) {
        item.Serialize(writer);
    }
    writer.EndArray();
    writer.EndObject();
    serialized_string = serialized.GetString();
}

std::vector<Infected> JsonHandler::deserialize_infected_list(char *received_message) {
    std::vector<Infected> infected_list;
    Infected *temp_infected;

    parse(received_message);
    for(auto& e : document.FindMember("infected")->value.GetArray()){
        temp_infected = new Infected();
        temp_infected->Deserialize(e.GetObject());
        infected_list.push_back(*temp_infected);
    }
    return infected_list;
}

std::string JsonHandler::getSerialized() const {
    return serialized_string;
}

void JsonHandler::serialize_stats(const std::vector<Country>& countries) {
    rapidjson::StringBuffer serialized;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(serialized);
    writer.StartObject();
    writer.Key("countries");
    writer.StartArray();
    for (const auto &country : countries) {
        writer.StartObject();

        writer.Key("country-name");
        writer.String(country.getName().c_str());

        writer.Key("stats");
        writer.StartObject();

        writer.Key("immune");
        writer.Int(country.getImmuneCount());

        writer.Key("infected");
        writer.Int(country.getInfectedCount());

        writer.Key("susceptible");
        writer.Int(country.getSusceptibleCount());

        writer.EndObject();
        writer.EndObject();
    }
    writer.EndArray();
    writer.EndObject();
    serialized_string = serialized.GetString();
}

void JsonHandler::accumulate_infected(char* received_message, World *world) {
    Infected *temp_infected;
    std::vector<Infected> *infected_list = &(world->getInfectedList());
    parse(received_message);

    for(auto& e : document.FindMember("infected")->value.GetArray()){
        temp_infected = new Infected();
        temp_infected->Deserialize(e.GetObject());
        infected_list->push_back(*temp_infected);
    }
    serialize_infected_list(*infected_list);
}

void JsonHandler::accumulate_stats(char* received_message, World *world) {
    parse(received_message);
    Country* current_country;
    for(auto& e : document.FindMember("countries")->value.GetArray()) {
        current_country = world->findCountryByName(e.FindMember("country-name")->value.GetString());
        current_country->setImmuneCount(current_country->getImmuneCount()
                                                    +e.FindMember("stats")->value.FindMember("immune")->value.GetInt());
        current_country->setInfectedCount(current_country->getInfectedCount()
                                        +e.FindMember("stats")->value.FindMember("infected")->value.GetInt());
        current_country->setSusceptibleCount(current_country->getSusceptibleCount()
                                        +e.FindMember("stats")->value.FindMember("susceptible")->value.GetInt());
    }
    serialize_stats(world->getCountries());
}

void JsonHandler::parse(char *received_message) {
    document.Parse<rapidjson::kParseStopWhenDoneFlag>((const char *) received_message);
}

void JsonHandler::update_stats(char *received_message, World *world) {
    parse(received_message);
    Country* current_country;
    for(auto& e : document.FindMember("countries")->value.GetArray()) {
        current_country = world->findCountryByName(e.FindMember("country-name")->value.GetString());
        current_country->setImmuneCount(e.FindMember("stats")->value.FindMember("immune")->value.GetInt());
        current_country->setInfectedCount(e.FindMember("stats")->value.FindMember("infected")->value.GetInt());
        current_country->setSusceptibleCount(e.FindMember("stats")->value.FindMember("susceptible")->value.GetInt());
    }

}

JsonHandler::JsonHandler() = default;

