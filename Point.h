//
// Created by dpaletti on 2021-03-09.
//

#ifndef VIRUS_SPREADING_MODEL_POINT_H
#define VIRUS_SPREADING_MODEL_POINT_H


class Point {
public:
    Point(float x, float y);

    Point();

    float getX() const;

    float getY() const;

    bool equals(Point a) const;
private:
    float x, y;

};


#endif //VIRUS_SPREADING_MODEL_POINT_H
