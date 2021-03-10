//
// Created by dpaletti on 2021-03-09.
//

#include "Grid.h"
#include <list>

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

void Grid::add_row(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    for (int row = number_of_active_rows - 1; row >= cell_to_fill_row; row--){
        for (int col = 0; col <= cell_to_fill_column; col++)
            cells[row + 1][col] = cells[row][col];
    }
    for (int col = 0; col < number_of_active_columns; col++){
        Cell *cell_beside = &cells[cell_to_fill_row + 1][col];
        cell_beside->setWidth(cells[cell_to_fill_row][cell_to_fill_column].getWidth() - country.getWidth());
        cell_beside->setAnchorPoint(Point(cell_beside->getAnchorPoint().getX(), cell_beside->getAnchorPoint().getY() + country.getWidth()));
        cells[cell_to_fill_row][col].setWidth(country.getWidth());
    }
    number_of_active_rows++;
}

void Grid::add_column(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    for (int col = number_of_active_columns - 1; col >= cell_to_fill_column; col--){
        for (int row = 0; row <= cell_to_fill_row; row++)
            cells[row][col + 1] = cells[row][col];
    }
    for (int row = 0; row < number_of_active_rows; row++){
        Cell *cell_beside = &cells[row][cell_to_fill_column + 1];
        cell_beside->setLength(cells[cell_to_fill_row][cell_to_fill_column].getLength() - country.getLength());
        cell_beside->setAnchorPoint( Point ((cell_beside->getAnchorPoint()).getX() + country.getLength(), cell_beside->getAnchorPoint().getY()));
        cells[row][cell_to_fill_column].setLength(country.getLength());
    }
    number_of_active_columns++;
}

bool Grid::fit_exact(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    Cell *cell = &cells[cell_to_fill_row][cell_to_fill_column];
    if (country.getWidth() == cell->getWidth() && country.getLength() != cell->getLength())
        add_column(cell_to_fill_row, cell_to_fill_column, country);

    else if(country.getLength() == cell->getLength() && country.getWidth() != cell->getWidth())
        add_row(cell_to_fill_row, cell_to_fill_column, country);

    else if (country.getLength() != cell->getLength() && country.getWidth() != cell->getWidth()){
        add_row(cell_to_fill_row, cell_to_fill_column, country);
        add_column(cell_to_fill_row, cell_to_fill_column, country);
    }

    cell->setIsOccupied(true);
    return true;
}

bool Grid::fit_length(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    return false;
}

bool Grid::fit_width(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    float acc = cells[cell_to_fill_row][cell_to_fill_column].getLength();
    std::list<Cell> filled_cells {};
    Cell current_cell;
    for (int col = cell_to_fill_column + 1; col < number_of_active_columns; col++){
        current_cell = cells[cell_to_fill_row][col];
        acc += current_cell.getLength();
        filled_cells.push_back(current_cell); //append
        if (acc >= country.getLength()){
            if (current_cell.getWidth() != country.getWidth())
                add_row(cell_to_fill_row, col, country);

            if (acc != country.getLength())
                add_column(cell_to_fill_row, col, country);

            for (auto &item : filled_cells) {
                item.setIsOccupied(true);
            }
            return true;
        }
        else if (current_cell.isOccupied())
            return false;
    }
    return false;
}

bool Grid::fit_length_width(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    return false;
}







