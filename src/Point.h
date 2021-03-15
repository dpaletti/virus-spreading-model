#ifndef VIRUS_SPREADING_MODEL_POINT_H
#define VIRUS_SPREADING_MODEL_POINT_H

#include <string>
#include <vector>
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/document.h"
#include <exception>

class Point {
public:
    Point(float x, float y);

    Point();

    float getX() const;

    float getY() const;

    bool equals(Point a) const;

    std::string toString();

    template <typename Writer>
    void Serialize(Writer& writer) const;
    void Deserialize(const rapidjson::Value &obj);

private:
    float x, y;

};


#endif //VIRUS_SPREADING_MODEL_POINT_H
