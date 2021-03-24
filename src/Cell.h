#ifndef VIRUS_SPREADING_MODEL_CELL_H
#define VIRUS_SPREADING_MODEL_CELL_H


#include "Point.h"

/**
 * Cell class represent a cell in the grid that constitutes the world
 */
class Cell {
public:
    /**
     * @param anchorPoint
     * @param length
     * @param width
     * @param isOccupied
     */
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
    /**
     * Represent where the cell is anchored in the grid
     */
    Point anchor_point;
    float length;
    float width;
    bool is_occupied;

};


#endif //VIRUS_SPREADING_MODEL_CELL_H
