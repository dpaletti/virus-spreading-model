//
// Created by dpaletti on 2021-03-09.
//

#include "Country.h"


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
    anchor_point = anchorPoint;
}

Country::Country(const std::string &name, float length, float width) :  name(name),
                                                                        length(length),
                                                                        width(width),
                                                                        anchor_point()
                                                                        {}
