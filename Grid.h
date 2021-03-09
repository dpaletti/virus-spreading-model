//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_GRID_H
#define VIRUS_SPREADING_MODEL_GRID_H


#include "Cell.h"

class Grid {
public:
    Grid(int number_of_countries, float world_length, float world_width);

    int getNumberOfActiveRows() const;

    void setNumberOfActiveRows(int numberOfActiveRows);

    int getNumberOfActiveColumns() const;

    void setNumberOfActiveColumns(int numberOfActiveColumns);

    Cell **getCells() const;


private:
    int number_of_active_rows;
    int number_of_active_columns;
    Cell **cells;

};


#endif //VIRUS_SPREADING_MODEL_GRID_H
