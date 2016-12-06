//
// Created by gabriel on 6.12.2016.
//

#ifndef GRAPHICSPROJECT_KEYFRAME_H
#define GRAPHICSPROJECT_KEYFRAME_H


#include <src/game/GameObject.h>

class KeyFrame {
    private:
        float time;
        Transform transform;
        bool reached = false;

    public:
        KeyFrame(float time, Vector3f pos, Vector3f rot, Vector3f sca) : time(time), transform(pos, rot, sca){}

        Transform getTransform(void){return transform;}
};


#endif //GRAPHICSPROJECT_KEYFRAME_H
