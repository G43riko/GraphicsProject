//
// Created by gabriel on 21.9.2016.
//


#include "utils.h"
int IdGenerator::counter = 0;
int IdGenerator::getId(void){
    return counter++;
}


