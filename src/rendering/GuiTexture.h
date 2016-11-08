//
// Created by gabriel on 1.11.2016.
//

#ifndef GRAPHICSPROJECT_GUITEXTURE_H
#define GRAPHICSPROJECT_GUITEXTURE_H


#include "../utils/Vectors.h"

class GuiTexture {
private:
    int texture;
    Vector2f position;
    Vector2f scale;
public:
    GuiTexture(int texture, const Vector2f & position, const Vector2f & scale){
        this -> texture = texture;
        this -> position = position;
        this -> scale = scale;
    }
    int getTexture(){
        return texture;
    }
    void setTexture(int id){
        texture = id;
    }
    Vector2f getPosition(){
        return position;
    }
    Vector2f getScale(){
        return scale;
    }
};


#endif //GRAPHICSPROJECT_GUITEXTURE_H
