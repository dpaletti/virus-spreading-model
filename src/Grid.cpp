#include "Grid.h"
#include <list>
#include <stdexcept>
#include <iostream>


Grid::Grid(int number_of_countries, float world_length, float world_width){
    number_of_active_rows = 1;
    number_of_active_columns = 1;
    cells = std::vector<std::vector<Cell>>(number_of_countries+1, std::vector<Cell>(number_of_countries+1));
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

std::vector<std::vector<Cell>>Grid::getCells() const {
    return cells;
}

Point Grid::place_country(Country country) {
    for(int j=0; j< getNumberOfActiveColumns(); j++){
        for(int i=0; i< getNumberOfActiveRows(); i++){
            if (cells[i][j].isOccupied())
                continue;
            if(country.getWidth() <= cells[i][j].getWidth() && country.getLength() <= cells[i][j].getLength()){
                // country fits in exactly one cell
                if (fit_exact(i, j, country))
                    return cells[i][j].getAnchorPoint();
            }
            else if(country.getWidth() > cells[i][j].getWidth() && country.getLength() <= cells[i][j].getLength()){
                // country fits length-wise but not width-wise
                if (fit_length(i, j, country))
                    return cells[i][j].getAnchorPoint();
            }
            else if(country.getWidth() <= cells[i][j].getWidth() && country.getLength() > cells[i][j].getLength()){
                // country fits width-wise but not length wise
                if (fit_width(i, j, country))
                    return cells[i][j].getAnchorPoint();
            }
            else{
                if (fit_length_width(i, j, country))
                    return cells[i][j].getAnchorPoint();
            }
        }
    }

    throw std::runtime_error("Could not place country " + country.getName() + ".");
}

void Grid::add_row(int cell_to_fill_row, int cell_to_fill_column, Country country, float acc) {
    for (int row = number_of_active_rows - 1; row >= cell_to_fill_row; row--){
        for (int col = 0; col <= number_of_active_columns -1; col++)
            cells[row + 1][col] = cells[row][col];
    }
    float cell_to_fill_width = cells[cell_to_fill_row][cell_to_fill_column].getWidth();
    for (int col = 0; col < number_of_active_columns; col++){
        Cell *cell_beside = &cells[cell_to_fill_row + 1][col];
        cell_beside->setWidth(cell_to_fill_width - country.getWidth() + acc);
        cell_beside->setAnchorPoint(Point(cell_beside->getAnchorPoint().getX(), cell_beside->getAnchorPoint().getY() + country.getWidth() - acc));
        cells[cell_to_fill_row][col].setWidth(country.getWidth() - acc);
    }
    number_of_active_rows++;
}

void Grid::add_column(int cell_to_fill_row, int cell_to_fill_column, Country country, float acc) {
    for (int col = number_of_active_columns - 1; col >= cell_to_fill_column; col--){
        for (int row = 0; row <= number_of_active_rows - 1; row++)
            cells[row][col + 1] = cells[row][col];
    }
    float cell_to_fill_length = cells[cell_to_fill_row][cell_to_fill_column].getLength();
    for (int row = 0; row < number_of_active_rows; row++){
        Cell *cell_beside = &cells[row][cell_to_fill_column + 1];
        cell_beside->setLength(cell_to_fill_length - country.getLength() + acc);
        cell_beside->setAnchorPoint( Point ((cell_beside->getAnchorPoint()).getX() + country.getLength() - acc, cell_beside->getAnchorPoint().getY()));
        cells[row][cell_to_fill_column].setLength(country.getLength() - acc);
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
    float acc = cells[cell_to_fill_row][cell_to_fill_column].getWidth();
    std::list<Cell*> filled_cells {};
    filled_cells.push_back(&cells[cell_to_fill_row][cell_to_fill_column]);
    Cell* current_cell;
    for (int row = cell_to_fill_row + 1; row < number_of_active_rows; row++){
        current_cell = &cells[row][cell_to_fill_column];
        if (!current_cell->isOccupied()){
            acc += current_cell->getWidth();
            filled_cells.push_back(current_cell); //append
            if (acc >= country.getWidth()){
                if (current_cell->getLength() != country.getLength())
                    add_column(row, cell_to_fill_column, country);

                if (acc != country.getWidth())
                    add_row(row, cell_to_fill_column, country,acc-current_cell->getWidth());

                for (auto &item : filled_cells) {
                    item->setIsOccupied(true);
                }
                return true;
            }
        }
        else
            return false;
    }
    return false;
}

bool Grid::fit_width(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    float acc = cells[cell_to_fill_row][cell_to_fill_column].getLength();
    std::list<Cell*> filled_cells {};
    filled_cells.push_back(&cells[cell_to_fill_row][cell_to_fill_column]);
    Cell* current_cell;
    for (int col = cell_to_fill_column + 1; col < number_of_active_columns; col++){
        current_cell = &cells[cell_to_fill_row][col];
        if (!current_cell->isOccupied()){
            acc += current_cell->getLength();
            filled_cells.push_back(current_cell); //append
            if (acc >= country.getLength()){
                if (current_cell->getWidth() != country.getWidth())
                    add_row(cell_to_fill_row, col, country);

                if (acc != country.getLength())
                    add_column(cell_to_fill_row, col, country,acc-current_cell->getLength());

                for (auto &item : filled_cells) {
                    item->setIsOccupied(true);
                }
                return true;
            }
        }

        else
            return false;
    }
    return false;
}

bool Grid::fit_length_width(int cell_to_fill_row, int cell_to_fill_column, Country country) {
    float acc_length = cells[cell_to_fill_row][cell_to_fill_column].getLength();
    float acc_width = cells[cell_to_fill_row][cell_to_fill_column].getWidth();
    std::list<std::pair<Cell*, std::pair<int, int>>> filled_cells_length {};
    filled_cells_length.push_back({&cells[cell_to_fill_row][cell_to_fill_column],{cell_to_fill_row,cell_to_fill_column}});
    std::list<Cell*> filled_cells_width {};
    filled_cells_width.push_back(&cells[cell_to_fill_row][cell_to_fill_column]);
    Cell* current_cell;
    for (int col = cell_to_fill_column + 1; col < number_of_active_columns; col++) {
        current_cell = &cells[cell_to_fill_row][col];
        if (!current_cell->isOccupied()){
            acc_length += current_cell->getLength();
            std::pair<int,int> index;
            index.first = cell_to_fill_row;
            index.second = col;
            std::pair<Cell*, std::pair<int, int>> list_item;
            list_item.first = current_cell;
            list_item.second = index;
            filled_cells_length.push_back(list_item);
            if (acc_length >= country.getLength())
                break;
        }
        else
            return false;
    }
    if (acc_length < country.getLength())
        return false;

    int last_col = -1;
    int last_row = -1;
    for (auto &item : filled_cells_length) {
        for (int row = cell_to_fill_row + 1; row < number_of_active_rows; row++){
            current_cell = &cells[row][item.second.second]; //col is second item
            if (!current_cell->isOccupied()){
                acc_width += current_cell->getWidth();
                filled_cells_width.push_back(current_cell);
                if (acc_width >= country.getWidth()){
                    last_col = item.second.second;
                    last_row = row;
                    break;
                }
            }
            else
                return false;
        }
        if (acc_width < country.getWidth())
            return false;
    }

    if (acc_width != country.getWidth())
        add_row(last_row, last_col, country, acc_width - (*filled_cells_width.back()).getWidth());
    if (acc_length != country.getLength())
        add_column(last_row, last_col, country, acc_length - filled_cells_length.back().first->getLength());
    for (auto &item : filled_cells_length)
        item.first->setIsOccupied(true);

    for (auto &item : filled_cells_width)
        item->setIsOccupied(true);

    return true;
}







