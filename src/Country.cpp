#include "Country.h"
#include <stdexcept>
#include <utility>
#include <iostream>

const std::string &Country::getName() const{
    return name;
}

float Country::getLength() const {
    return length;
}

float Country::getWidth() const {
    return width;
}

Point &Country::getAnchorPoint() {
    return anchor_point;
}

void Country::setAnchorPoint(const Point &anchorPoint) {
    if(anchor_point.getX() != -1 || anchor_point.getY() != -1)
        throw std::runtime_error("Setting an already set anchor point. Original point:(" +
            std::to_string(anchor_point.getX()) + "," + std :: to_string(anchor_point.getY()) + ") New Point: (" +
            std::to_string(anchorPoint.getX()) + "," + std :: to_string(anchorPoint.getY()) + ")" );
    anchor_point = anchorPoint;
}

Country::Country(std::string name, float length, float width) :  name(std::move(name)),
                                                                        length(length),
                                                                        width(width),
                                                                        anchor_point()
                                                                        {}

std::vector<Country> Country::buildCountries(std::list<std::pair<float, float>> countries) {
    std::vector<Country> out {};
    int i = 0;
    for(auto const& value: countries) {
        out.emplace_back(Country("country-" + std::to_string(i), value.second, value.first));
        i++;
    }
    return out;
}

void Country::updateImmuneCount() {
    immune_count++;
}

void Country::updateInfectedCount() {
    infected_count++;
}

void Country::updateSusceptibleCount() {
    susceptible_count++;
}

void Country::resetCounters() {
    immune_count = 0;
    infected_count = 0;
    susceptible_count = 0;
}

Country::Country() = default;


bool operator==(const Country &c1, const Country& c2) {
    return c1.getName() == c2.getName();
}

void Country::printStats(){
    std::cout << "Country " << name << " has " << infected_count << " infected, " << immune_count << " immune and " << susceptible_count << " susceptible." << std::endl;
}

int Country::getImmuneCount() const {
    return immune_count;
}

int Country::getInfectedCount() const {
    return infected_count;
}

int Country::getSusceptibleCount() const {
    return susceptible_count;
}

void Country::setImmuneCount(int immuneCount) {
    immune_count = immuneCount;
}

void Country::setInfectedCount(int infectedCount) {
    infected_count = infectedCount;
}

void Country::setSusceptibleCount(int susceptibleCount) {
    susceptible_count = susceptibleCount;
}
