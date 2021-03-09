//
// Created by dpaletti on 2021-03-09.
//

#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

Point::Point() : x(-1), y(-1){}

