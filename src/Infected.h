
#ifndef VIRUS_SPREADING_MODEL_INFECTED_H
#define VIRUS_SPREADING_MODEL_INFECTED_H


#include "Point.h"

class Infected {
private:
    Point position;
    std::string id;
public:
    Infected();

    Infected(const Point &position, const std::string &id);

    template <typename Writer>
    void Serialize(Writer& writer) const;
};



#endif //VIRUS_SPREADING_MODEL_INFECTED_H
