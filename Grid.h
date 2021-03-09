//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_GRID_H
#define VIRUS_SPREADING_MODEL_GRID_H


#include "Cell.h"
#include "Country.h"

class Grid {
public:
    Grid(int number_of_countries, float world_length, float world_width);

    int getNumberOfActiveRows() const;

    void setNumberOfActiveRows(int numberOfActiveRows);

    int getNumberOfActiveColumns() const;

    void setNumberOfActiveColumns(int numberOfActiveColumns);

    Cell **getCells() const;

    Point place_country(Country country) const;

private:
    int number_of_active_rows;
    int number_of_active_columns;
    Cell **cells;
    void fit_country(Cell cell, Country country) const;
    void try_fit_country(Cell cell, Country country) const;
    void try_fit_country_width_wise(Cell cell, Country country) const;
    void try_fit_country_length_wise(Cell cell, Country country) const;
    Cell **expand(Cell toExpand, Country country, Cell toFill) const;
};


#endif //VIRUS_SPREADING_MODEL_GRID_H
