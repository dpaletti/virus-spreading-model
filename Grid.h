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

    Point place_country(Country country);

private:
    int number_of_active_rows;
    int number_of_active_columns;
    Cell **cells;
    //add row and column after a country has been added
    void add_row(int cell_to_fill_row, int cell_to_fill_column, Country country);
    void add_column(int cell_to_fill_row, int cell_to_fill_column, Country country);

    bool fit_exact (int cell_to_fill_row, int cell_to_fill_column, Country country);
    bool fit_length (int cell_to_fill_row, int cell_to_fill_column, Country country);
    bool fit_width (int cell_to_fill_row, int cell_to_fill_column, Country country);
    bool fit_length_width (int cell_to_fill_row, int cell_to_fill_column, Country country);


};


#endif //VIRUS_SPREADING_MODEL_GRID_H
