
#ifndef VIRUS_SPREADING_MODEL_INFECTED_H
#define VIRUS_SPREADING_MODEL_INFECTED_H


#include "Point.h"
#include "rapidjson/document.h"
#include "Contact.h"
class Contact;
class Infected {
private:
    Point position;
    std::string id;
public:
    Infected();

    Infected(const Point &position, std::string id);

    void Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
    void Deserialize(const rapidjson::Value &obj);

    const std::string &getId() const;

    const Point &getPosition() const;
    bool operator<(const Infected& i){
        return id < i.getId();
    }
    bool operator<(const Contact& c);
    bool operator==(const Infected &i) {
        return id == i.getId();
    }
    Infected operator*(){
        return *this;

    }

    bool operator==(const Contact &c);
};

#endif //VIRUS_SPREADING_MODEL_INFECTED_H
