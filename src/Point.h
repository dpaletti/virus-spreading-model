#ifndef VIRUS_SPREADING_MODEL_POINT_H
#define VIRUS_SPREADING_MODEL_POINT_H

#include <string>
#include <vector>
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/document.h"
#include <exception>

class Point {
private:
    float x, y;

public:
    Point(float x, float y);

    Point();

    float getX() const;

    float getY() const;

    bool equals(Point a) const;

    float getDistance(Point a);

    std::string toString();

    void Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer) const;
    void Deserialize(const rapidjson::Value &obj);


};


#endif //VIRUS_SPREADING_MODEL_POINT_H
