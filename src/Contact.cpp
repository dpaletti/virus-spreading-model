#include "Contact.h"
#include "Infected.h"
#include <utility>

Contact::Contact() = default;

Contact::Contact(std::string id, float contactTime) : id(std::move(id)), contactTime(contactTime) {}

float Contact::getContactTime() const {
    return contactTime;
}

void Contact::setContactTime(float d) {
    Contact::contactTime = d;
}

const std::string &Contact::getId() const {
    return id;
}

bool Contact::operator==(const Infected& i){
    return i.getId() == id;
}
