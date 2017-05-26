//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_MODEL_H
#define GAMEENGINE_MODEL_H

#include <src/rendering/model/Mesh.h>

class Model{
    PointerMesh _mesh;
protected:
    VectorUI indices;
    VectorF finalPositions;
    VectorF finalNormals;
    VectorF finalTangents;
    VectorF finalTextures;

    virtual inline void generateModel(void) = 0;

    void setMesh(){
        _mesh = Mesh::create(finalPositions, finalTextures, finalNormals, finalTangents, indices);
    }
public:
    inline PointerMesh getMesh(void) const{ return _mesh; }
};
#endif //GAMEENGINE_MODEL_H
