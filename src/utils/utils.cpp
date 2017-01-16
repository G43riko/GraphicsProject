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
std::vector<Vector3f> getKerner(void){
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;

    std::vector<Vector3f> ssaoKernel;
    for(int i=0 ; i<64 ; i++){
        float scale = (float)i / 64;
        scale =  lerp(0.1f, 1.0f, scale * scale);
        Vector3f sample = Vector3f(randomFloats(generator) * 2 - 1, randomFloats(generator) * 2 - 1, randomFloats(generator)).normalize();
        sample *=randomFloats(generator) * scale;
        ssaoKernel.push_back(sample);
    }
    return ssaoKernel;
}