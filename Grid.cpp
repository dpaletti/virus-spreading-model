//
// Created by dpaletti on 2021-03-09.
//

#include "Grid.h"

Grid::Grid(int number_of_countries, float world_length, float world_width){
    number_of_active_rows = 1;
    number_of_active_columns = 1;
    Cell temp[number_of_countries+1][number_of_countries+1];
    cells = (Cell**)temp;
    cells[0][0] = Cell(Point(0, 0), world_length, world_width, false);}

int Grid::getNumberOfActiveRows() const {
    return number_of_active_rows;
}

void Grid::setNumberOfActiveRows(int numberOfActiveRows) {
    number_of_active_rows = numberOfActiveRows;
}

int Grid::getNumberOfActiveColumns() const {
    return number_of_active_columns;
}

void Grid::setNumberOfActiveColumns(int numberOfActiveColumns) {
    number_of_active_columns = numberOfActiveColumns;
}

Cell **Grid::getCells() const {
    return cells;
}

int Grid::getNumberOfActiveRows() const {
    return number_of_active_rows;
}

int Grid::getNumberOfActiveColumns() const {
    return number_of_active_columns;
}

Cell **Grid::getCells() const {
    return cells;
}

void Grid::setNumberOfActiveRows(int numberOfActiveRows) {
    number_of_active_rows = numberOfActiveRows;
}

void Grid::setNumberOfActiveColumns(int numberOfActiveColumns) {
    number_of_active_columns = numberOfActiveColumns;
}

