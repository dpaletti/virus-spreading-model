#ifndef VIRUS_SPREADING_MODEL_INPUTPARSER_H
#define VIRUS_SPREADING_MODEL_INPUTPARSER_H
#include <string>
#include "rapidjson/document.h"
#include <list>


class InputParser {
public:
    InputParser(const std::string& file_path);
    int getIndividualsNumber();
    int getInfectedNumber();
    std::pair<float, float> getWorldSize();
    std::list<std::pair<float, float>> getCountries();
    float getVelocity();
    float getMaximumSpreadingDistance();
    int getTimeStep();

private:
    rapidjson::Document document;



};


#endif //VIRUS_SPREADING_MODEL_INPUTPARSER_H
