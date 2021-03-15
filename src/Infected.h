
#ifndef VIRUS_SPREADING_MODEL_INFECTED_H
#define VIRUS_SPREADING_MODEL_INFECTED_H


#include "Point.h"
#include "rapidjson/document.h"

class Infected {
private:
    Point position;
    std::string id;
public:
    Infected();

    Infected(const Point &position, const std::string &id);

    template <typename Writer>
    void Serialize(Writer& writer) const;
    void Deserialize(const rapidjson::Value &obj);

};



#endif //VIRUS_SPREADING_MODEL_INFECTED_H
