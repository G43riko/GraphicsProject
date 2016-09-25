//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include "Texture2D.cpp"


class Material {
    private:
        Texture2D * diffuse;
    public:
        Material(Texture2D * diffuse){
            this -> diffuse = diffuse;
        }
        Texture2D * getDiffuse(){
            return diffuse;
        }
};


#endif //GRAPHICSPROJECT_MATERIAL_H
