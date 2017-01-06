//
// Created by gabriel on 6.12.2016.
//

#ifndef GRAPHICSPROJECT_ANIMATION_H
#define GRAPHICSPROJECT_ANIMATION_H


#include <vector>
#include <src/components/KeyFrame.h>
#include "GameObject.h"

class Animation {
    PointerGameObject object;
    std::vector<KeyFrame> frames;

    float actualTime = 0;
    float targetTime = 0;

    KeyFrame * actualFrame = nullptr;
    KeyFrame * nextFrame = nullptr;
    bool running = false;

    Animation(PointerGameObject object){
        this -> object = object;
    }
    void update(float delate){

    }

    void start(){
        running = true;
        if(frames.size() < 2){
            Logger::error("Nieje možné spustiť animácia s menej ako 2 keyframamy");
            exit(1);
        }
    }

    void addFrame(KeyFrame frame){
        if(frames.empty())
            actualFrame = &frame;

        frames.push_back(frame);
    }
};


#endif //GRAPHICSPROJECT_ANIMATION_H
