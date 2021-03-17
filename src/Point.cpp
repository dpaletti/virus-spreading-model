#include "Point.h"
#include "rapidjson/document.h"
#include <math.h>

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

void Point::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer) const {
    writer.StartObject();
    writer.Key("x");
    writer.Double((double)x);
    writer.Key("y");
    writer.Double((double)y);
    writer.EndObject();

}

void Point::Deserialize(const rapidjson::Value &obj) {
    x = (float)obj.FindMember("x")->value.GetDouble();
    y = (float)obj.FindMember("y")->value.GetDouble();
}

float Point::getDistance(Point a) {
    //TODO:Check if return double
    return sqrt(pow(getX(),2) - pow(a.getX(),2) + pow(getY(),2) - pow(a.getY(),2));
}
