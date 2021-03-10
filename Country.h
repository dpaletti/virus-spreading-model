#ifndef VIRUS_SPREADING_MODEL_COUNTRY_H
#define VIRUS_SPREADING_MODEL_COUNTRY_H


#include "Point.h"
#include <string>

class Country {
public:

    Country(const std::string &name, float length, float width);

    const std::string &getName() const;

    float getLength() const;

    float getWidth() const;

    const Point &getAnchorPoint() const;

    void setAnchorPoint(const Point &anchorPoint);

private:
    std::string name;
    float length, width;
    Point anchor_point;
};


#endif //VIRUS_SPREADING_MODEL_COUNTRY_H
