#ifndef VIRUS_SPREADING_MODEL_CONTACT_H
#define VIRUS_SPREADING_MODEL_CONTACT_H


#include <string>
#include "Infected.h"
class Infected;
/**
 * Class represents a contact associated to an individual, each individual keeps a vector of his contacts
 */
class Contact {
public:
    Contact();
    /**
     *
     * @param id
     * @param contactTime
     */
    Contact(std::string id, float contactTime);

    float getContactTime() const;

    void setContactTime(float contactTime);

    const std::string &getId() const;

    bool operator<(const Contact& c){
        return id < c.getId();
    }

    bool operator==(const Infected& i);
private:
    /**
     * id represents the id of the individual that came in contact with the one keeping the information
     */
    std::string id;
    float contactTime;
};


#endif //VIRUS_SPREADING_MODEL_CONTACT_H
