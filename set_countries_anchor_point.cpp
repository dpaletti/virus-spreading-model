//
// Created by dpaletti on 2021-03-09.
//

#include "World.h"
#include "Cell.h"

World set_countries_anchor_points(World world){
    int number_of_countries = world.getCountries().size();
    Cell cells[number_of_countries+1][number_of_countries+1];
    cells[0][0] = Cell(Point(0, 0), world.getLength(), world.getWidth(), 0);

}
