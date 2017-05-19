//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_GOBJECTS_H
#define GAMEENGINE_GOBJECTS_H

#include "Mesh.h"
#include <src/Messages.h>


namespace GObjects{
    inline PointerMesh createLine(Vector3f a, Vector3f b){
        return Mesh::create({a.x, a.y, a.z, b.x, b.y, b.z}, {0, 1});
    }
    inline PointerMesh createLine(VectorV3 points){
        VectorF vertices;
        VectorUI indices;
        unsigned int index = 0;
        for(auto point : points){
            vertices.push_back(point.x);
            vertices.push_back(point.y);
            vertices.push_back(point.z);
            indices.push_back(index++);
        }
        return Mesh::create(vertices, indices);
    }
    inline PointerMesh createPlane(float size, Directions direction = Directions::FORWARD){
        float sizeX = size;
        float sizeY = size;
        //float sizeZ = size;
        VectorF vertices;
        if(direction == Directions::FORWARD){
            vertices = {-sizeX,  sizeY, 0.0f,
                        -sizeX, -sizeY, 0.0f,
                         sizeX, -sizeY, 0.0f,
                         sizeX,  sizeY, 0.0f};
        }
        else if(direction == Directions::BACK){
            vertices = { sizeX, -sizeY, 0.0f,
                         sizeX,  sizeY, 0.0f,
                        -sizeX,  sizeY, 0.0f,
                        -sizeX, -sizeY, 0.0f};
        }
        else{
            throw getMessage(WRONG_DIRECTION);
        }
        return Mesh::create(vertices, {0.0f, 0.0f,
                                       0.0f, 1.0f,
                                       1.0f, 1.0f,
                                       1.0f, 0.0f},
                                      {0, 1, 3,
                                       3, 1, 2});
    }
    /*
    PointerMesh plane = PointerMesh(new Mesh({-1.0f,  1.0f, 0.0f,
                                              -1.0f, -1.0f, 0.0f,
                                               1.0f, -1.0f, 0.0f,
                                               1.0f,  1.0f, 0.0f},
                                             { 0.0f, 0.0f,
                                               0.0f, 1.0f,
                                               1.0f, 1.0f,
                                               1.0f, 0.0f},
                                             { 0, 1, 3,
                                               3, 1, 2}));

    PointerMesh cube = PointerMesh(new Mesh({-0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,
                                             -0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                                              0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                                             -0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,
                                             -0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,
                                             -0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f},
                                            { 0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,
                                              0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0},
                                            { 0,1,3,3,1,2,4,5,7,7,5,6,8,9,11,11,9,10,12,13,
                                              15,15,13,14,16,17,19,19,17,18,20,21,23,23,21,22}));
                                              */
}
#endif //GAMEENGINE_GOBJECTS_H
