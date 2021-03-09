//
// Created by dpaletti on 2021-03-09.
//

#include "Cell.h"

Cell::Cell(const Point &anchorPoint, float length, float width, bool isOccupied) : anchor_point(anchorPoint),
                                                                                   length(length), width(width),
                                                                                   is_occupied(isOccupied) {}

const Point &Cell::getAnchorPoint() const {
    return anchor_point;
}

float Cell::getLength() const {
    return length;
}

float Cell::getWidth() const {
    return width;
}

bool Cell::isOccupied() const {
    return is_occupied;
}

void Cell::setAnchorPoint(const Point &anchorPoint) {
    anchor_point = anchorPoint;
}

void Cell::setLength(float length) {
    Cell::length = length;
}

void Cell::setWidth(float width) {
    Cell::width = width;
}

void Cell::setIsOccupied(bool isOccupied) {
    is_occupied = isOccupied;
}

Cell::Cell() {}

bool Cell::equals(Cell a) {
    return a.getAnchorPoint().equals(getAnchorPoint());
}
