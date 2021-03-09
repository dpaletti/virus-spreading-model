//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_WORLD_H
#define VIRUS_SPREADING_MODEL_WORLD_H

#include <list>
#include "Country.h"
#include "Grid.h"

class World {
public:
    World(float length, float width, const std::list<Country> &countries);

    float getLength() const;

    float getWidth() const;

    const std::list<Country> &getCountries() const;
    void set_countries_anchor_point() const;

private:
    float length, width;
    std::list<Country> countries;
    void place_country(Country country, Grid grid) const;
    void
    fit_country() const;
    void try_fit_country() const;
    void try_fit_country_width_wise() const;
    void try_fit_country_length_wise() const;

};


#endif //VIRUS_SPREADING_MODEL_WORLD_H
