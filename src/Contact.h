#ifndef VIRUS_SPREADING_MODEL_CONTACT_H
#define VIRUS_SPREADING_MODEL_CONTACT_H


#include <string>
#include "Infected.h"

class Contact {
public:
    Contact();

    Contact(std::string id, float contactTime);

    float getContactTime() const;

    void setContactTime(float contactTime);

    const std::string &getId() const;

    bool operator<(const Contact& c){
        return id < c.getId();
    }

    bool operator==(Infected& i){
        return i.getId() == id;
    }
private:
    std::string id;
    float contactTime;
};


#endif //VIRUS_SPREADING_MODEL_CONTACT_H
