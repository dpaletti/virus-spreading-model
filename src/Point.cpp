#include "Point.h"

Point::Point(float x, float y) : x(x), y(y) {}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

Point::Point() : x(-1), y(-1){}

bool Point::equals(Point a) const {
    return (a.getX() == getX() && a.getY() == getY());
}

std::string Point::toString() {
    std::string point = "(" +  std::to_string(x) + "," + std::to_string(y) +")";
    return point;
}
