#include "Infected.h"

#include <utility>
#include "Contact.h"
#include "rapidjson/document.h"


void Infected::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) const {
    writer.StartObject();
    writer.Key("point");
    position.Serialize(writer);
    writer.Key("id");
    writer.String(id.c_str());
    writer.EndObject();

}

Infected::Infected() = default;

Infected::Infected(const Point &position, std::string id) : position(position), id(std::move(id)) {}

void Infected::Deserialize(const rapidjson::Value &obj) {
    id = obj.FindMember("id")->value.GetString();
    position = Point();
    position.Deserialize(obj.FindMember("point")->value);
}

const std::string &Infected::getId() const {
    return id;
}

const Point &Infected::getPosition() const {
    return position;
}

bool Infected::operator<(const Contact& c){
    return id < c.getId();
}
bool Infected::operator==(const Contact &c){
    return id == c.getId();
}