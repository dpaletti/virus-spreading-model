#include "Point.h"
#include "rapidjson/document.h"


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

template<typename Writer>
void Point::Serialize(Writer &writer) const {
    writer.StartObject();
    writer.String("x");
    writer.Double((double)x);
    writer.String("y");
    writer.Double((double)y);
    writer.EndObject();

}

void Point::Deserialize(const rapidjson::Value &obj) {
    x = (float)obj.FindMember("x")->value.GetDouble();
    y = (float)obj.FindMember("y")->value.GetDouble();
}
