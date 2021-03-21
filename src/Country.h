#ifndef VIRUS_SPREADING_MODEL_COUNTRY_H
#define VIRUS_SPREADING_MODEL_COUNTRY_H


#include "Point.h"
#include <string>
#include <vector>
#include <list>


class Country {
public:

    Country(std::string name, float length, float width);

    Country();

    const std::string &getName() const;

    float getLength() const;

    float getWidth() const;

    Point &getAnchorPoint();

    void setAnchorPoint(const Point &anchorPoint);

    static std::vector<Country>buildCountries(std::list<std::pair<float, float>> countries);

    void updateImmuneCount();

    void updateInfectedCount();

    int getImmuneCount() const;

    int getInfectedCount() const;

    int getSusceptibleCount() const;

    void updateSusceptibleCount();

    void resetCounters();

    void printStats();


private:
    std::string name;
    float length{}, width{};
    Point anchor_point;
    int immune_count = 0;
public:
    void setImmuneCount(int immuneCount);

    void setInfectedCount(int infectedCount);

    void setSusceptibleCount(int susceptibleCount);

private:
    int infected_count = 0;
    int susceptible_count = 0;
};



#endif //VIRUS_SPREADING_MODEL_COUNTRY_H
