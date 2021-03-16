#include "Contact.h"

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
