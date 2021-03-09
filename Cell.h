//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_CELL_H
#define VIRUS_SPREADING_MODEL_CELL_H


#include "Point.h"

class Cell {
public:
    Cell(const Point &anchorPoint, float length, float width, bool isOccupied);

    Cell();

    const Point &getAnchorPoint() const;

    float getLength() const;

    float getWidth() const;

    bool isOccupied() const;

    void setAnchorPoint(const Point &anchorPoint);

    void setLength(float length);

    void setWidth(float width);

    void setIsOccupied(bool isOccupied);

    bool equals(Cell a);

private:
    Point anchor_point;
    float length;
    float width;
    bool is_occupied;

};


#endif //VIRUS_SPREADING_MODEL_CELL_H
