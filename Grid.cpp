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

Point Grid::place_country(Country country) const {
    for(int i=0; i< getNumberOfActiveRows(); i++){
        for(int j=0; j< getNumberOfActiveColumns(); j++){
            if(country.getWidth() <= getCells()[i][j].getWidth() && country.getLength() <= getCells()[i][j].getLength()){
                // country fits in exactly one cell
            }
            else if(country.getWidth() > getCells()[i][j].getWidth() && country.getLength() <= getCells()[i][j].getLength()){
                // country fits length-wise but not width-wise
            }
            else if(country.getWidth() <= getCells()[i][j].getWidth() && country.getLength() > getCells()[i][j].getLength()){
                // country fits width-wise but not length wise
            }
            else{

            }
        }
    }
}

void Grid::fit_country(Cell cell, Country country) const {

}

void Grid::try_fit_country(Cell cell, Country country) const {

}

void Grid::try_fit_country_width_wise(Cell cell, Country country) const {

}

void Grid::try_fit_country_length_wise(Cell cell, Country country) const {

}

Cell **Grid::expand(Cell toExpand, Country country, Cell toFill) const {
    if(toExpand.equals(toFill)){
        // Calling a function that expands in the same cell

        // return
    }
    // Calling a function that expands in a different cell
}






