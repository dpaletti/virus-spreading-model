//
// Created by dpaletti on 2021-03-14.
//

#ifndef VIRUS_SPREADING_MODEL_INDIVIDUAL_H
#define VIRUS_SPREADING_MODEL_INDIVIDUAL_H


#include <utility>

class Individual {
private:
    std::pair<float, float> direction;
    bool isInfected;
    bool isImmune;
    std::pair<float, float> position;

};


#endif //VIRUS_SPREADING_MODEL_INDIVIDUAL_H
