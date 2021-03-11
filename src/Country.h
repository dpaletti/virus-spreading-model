#ifndef VIRUS_SPREADING_MODEL_COUNTRY_H
#define VIRUS_SPREADING_MODEL_COUNTRY_H


#include "Point.h"
#include <string>
#include <vector>
#include <list>


class Country {
public:

    Country(const std::string &name, float length, float width);

    Country();

    const std::string &getName() const;

    float getLength() const;

    float getWidth() const;

    Point &getAnchorPoint();

    void setAnchorPoint(const Point &anchorPoint);

    static std::vector<Country>buildCountries(std::list<std::pair<float, float>> countries);

private:
    std::string name;
    float length{}, width{};
    Point anchor_point;
};


#endif //VIRUS_SPREADING_MODEL_COUNTRY_H
