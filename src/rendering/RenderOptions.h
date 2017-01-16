//
// Created by gabriel on 15.1.2017.
//

#ifndef GRAPHICSPROJECT_RENDEROPTIONS_H
#define GRAPHICSPROJECT_RENDEROPTIONS_H

#include <map>

class RenderOptions{
private:
    std::map<int, bool> options = std::map<int, bool>();
public:
    const static int RENDER_TEXTURE             = 1;
    const static int RENDER_NORMAL_MAP          = 2;
    const static int RENDER_LIGHT               = 3;
    const static int RENDER_SPECULAR            = 4;
    const static int RENDER_FOG                 = 5;
    const static int RENDER_ENVIRONMENTAL_MAP   = 6;
    const static int RENDER_WATER               = 7;
    const static int RENDER_SHADOW              = 8;
    const static int USE_DEFERRED_RENDERER      = 9;
    const static int RENDER_GREYSCALE           = 10;
    const static int RENDER_INVERT              = 11;
    const static int RENDER_WIREFRAMES          = 12;
//    const static int USE_DEFERRED_RENDERER    = 13;

    void turnOnOption(int val){
        options[val] = true;
    };
    void turnOffOption(int val){
        options[val] = false;
    };
    void toggleOption(int val){
        options[val] = !options[val];
    };
    bool getOption(int val){
        return options[val];
    };
};


#endif //GRAPHICSPROJECT_RENDEROPTIONS_H
