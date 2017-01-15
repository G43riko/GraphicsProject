//
// Created by gabriel on 21.9.2016.
//


#include "utils.h"
int IdGenerator::counter = 0;
int IdGenerator::getId(void){
    return counter++;
}


double random(double LO, double HI){
    return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    //return min + fmod(rand(), max - min + 1);
}