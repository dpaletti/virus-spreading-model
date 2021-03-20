#include "JsonHandler.h"

void JsonHandler::serialize_list(const std::vector<Infected> &infected_list) {
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(serialized);
    writer.StartObject();
    writer.Key("infected");
    writer.StartArray();
    for (const auto &item : infected_list) {
        item.Serialize(writer);
    }
    writer.EndArray();
    writer.EndObject();
}

std::vector<Infected> JsonHandler::deserialize_list(const char *current_serialized_infected) {
//TODO not working current_serialized_infected prints out weird things
    std::vector<Infected> infected_list;
    rapidjson::Document document;
    Infected *temp_infected;

    document.Parse<rapidjson::kParseStopWhenDoneFlag>(current_serialized_infected);
    for(auto& e : document.FindMember("infected")->value.GetArray()){
        try {
            temp_infected = new Infected();
        }catch(std::bad_alloc&){
            printf("Bad Alloc at deserialize list");
            abort();
        }
        temp_infected->Deserialize(e.GetObject());
        infected_list.push_back(*temp_infected);
    }
    return infected_list;
}

const rapidjson::StringBuffer &JsonHandler::getSerialized() const {
    return serialized;
}

JsonHandler::JsonHandler() = default;

