//
// Created by gabriel on 21.9.2016.
//


#include "utils.h"

int IdGenerator::getId(void){
    int result = rand();
    while(ides.find(result) != ides.end())
        result = rand();

    ides.insert(result);
    return result;
}
std::set<int> IdGenerator::ides = std::set<int>();


