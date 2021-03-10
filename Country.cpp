#include "Country.h"
#include <stdexcept>

const std::string &Country::getName() const {
    return name;
}

float Country::getLength() const {
    return length;
}

float Country::getWidth() const {
    return width;
}

const Point &Country::getAnchorPoint() const {
    return anchor_point;
}

void Country::setAnchorPoint(const Point &anchorPoint) {
    if(anchor_point.getX() != -1 || anchor_point.getY() != -1)
        throw std::runtime_error("Setting an already set anchor point. Original point:(" +
            std::to_string(anchor_point.getX()) + "," + std :: to_string(anchor_point.getY()) + ") New Point: (" +
            std::to_string(anchorPoint.getX()) + "," + std :: to_string(anchorPoint.getY()) + ")" );
    anchor_point = anchorPoint;
}

Country::Country(const std::string &name, float length, float width) :  name(name),
                                                                        length(length),
                                                                        width(width),
                                                                        anchor_point()
                                                                        {}
