//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_GRID_H
#define VIRUS_SPREADING_MODEL_GRID_H


#include "Cell.h"
#include "Country.h"

/**
 * Grid is an abstraction of the structure of the world used to place countries in the beginning of the simulation
 */
class Grid {
public:
    Grid(int number_of_countries, float world_length, float world_width);

    int getNumberOfActiveRows() const;

    void setNumberOfActiveRows(int numberOfActiveRows);

    int getNumberOfActiveColumns() const;

    void setNumberOfActiveColumns(int numberOfActiveColumns);

    std::vector<std::vector<Cell>> getCells() const;
    /**
     * Used to place a country in the grid
     * @param country
     * @return
     */
    Point place_country(Country country);

private:
    /**
     * Number of rows used in the cells matrix
     */
    int number_of_active_rows;
    /**
     * Number of columns used in the cells matrix
     */
    int number_of_active_columns;
    /**
     * Matrix used to place countries incrementally while keeping all the cells either occupied or unoccupied
     */
    std::vector<std::vector<Cell>> cells;
    /**
     * Used to add a row in the matrix after a country is added to keep the cells either occupied or unoccupied
     * @param cell_to_fill_row
     * @param cell_to_fill_column
     * @param country
     * @param acc
     */
    void add_row(int cell_to_fill_row, int cell_to_fill_column, Country country, float acc=0);
    /**
     * Used to add a column in the matrix after a country is added to keep the cells either occupied or unoccupied
     * @param cell_to_fill_row
     * @param cell_to_fill_column
     * @param country
     * @param acc
     */
    void add_column(int cell_to_fill_row, int cell_to_fill_column, Country country, float acc=0);
    /**
     * Used to place a country in a cell that fits both width-wise and length-wise. Adjusts the matrix accordingly
     * to keep all the cells either occupied or unoccupied.
     * @param cell_to_fill_row Row of the chosen cell
     * @param cell_to_fill_column Column of the chosen cell
     * @param country Country to place
     * @return Returns true if the country has been placed, false otherwise
     */
    bool fit_exact (int cell_to_fill_row, int cell_to_fill_column, Country country);
    /**
     * Used to place a country in a cell that fits lenght-wise but not width-wise. It will search for space
     * on the neighboring cells in the same column (expand width-wise). Adjusts the matrix accordingly
     * to keep all the cells either occupied or unoccupied.
     * @param cell_to_fill_row Row of the chosen cell
     * @param cell_to_fill_column Column of the chosen cell
     * @param country Country to place
     * @return Returns true if the country has been placed, false otherwise
     */
    bool fit_length (int cell_to_fill_row, int cell_to_fill_column, Country country);
    /**
     * Used to place a country in a cell that fits width-wise but not length-wise. It will search for space
     * on the neighboring cells in the same row(expand length-wise). Adjusts the matrix accordingly
     * to keep all the cells either occupied or unoccupied.
     * @param cell_to_fill_row Row of the chosen cell
     * @param cell_to_fill_column Column of the chosen cell
     * @param country Country to place
     * @return Returns true if the country has been placed, false otherwise
     */
    bool fit_width (int cell_to_fill_row, int cell_to_fill_column, Country country);
    /**
     * Used to place a country in a cell that fits neither width-wise nor length-wise. It will search for space
     * on the neighboring cells in neighboring rows and columns(expand length-wise and width-wise).
     * Adjusts the matrix accordingly to keep all the cells either occupied or unoccupied.
     * @param cell_to_fill_row Row of the chosen cell
     * @param cell_to_fill_column Column of the chosen cell
     * @param country Country to place
     * @return Returns true if the country has been placed, false otherwise
     */
    bool fit_length_width (int cell_to_fill_row, int cell_to_fill_column, Country country);


};


#endif //VIRUS_SPREADING_MODEL_GRID_H
