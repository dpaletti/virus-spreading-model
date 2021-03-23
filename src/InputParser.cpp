#include "InputParser.h"
#include <string>
#include <fstream>
#include <array>
#include <list>
#include "rapidjson/document.h"

InputParser::InputParser(const std::string& file_path) {
    std::ifstream t(file_path);
    if (!t.good()){
        printf("\n\n Could not find configuration file at %s\n\n", file_path.c_str());
        abort();
    }
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    const char* file_content = str.c_str();
    document.Parse(file_content);
}

int InputParser::getIndividualsNumber() {
    return document["individuals_number"].GetInt();
}

int InputParser::getInfectedNumber() {
    return document["infected_number"].GetInt();
}

std::pair<float, float> InputParser::getWorldSize() {
    return {document["world"]["width"].GetFloat(), document["world"]["length"].GetFloat()};
}

std::list<std::pair<float, float>> InputParser::getCountries() {
    rapidjson::Value& a = document["countries"];
    std::list<std::pair<float, float>> country_list {};
    for (auto& v : a.GetArray()){
        float w = v["width"].GetFloat();
        float l = v["length"].GetFloat();
        country_list.emplace_back(w, l);
    }
    return country_list;
}

float InputParser::getVelocity() {
    return document["velocity"].GetFloat();
}

float InputParser::getMaximumSpreadingDistance() {
    return document["maximum_spreading_distance"].GetFloat();
}

float InputParser::getTimeStep() {
    return document["time_step"].GetFloat();
}
