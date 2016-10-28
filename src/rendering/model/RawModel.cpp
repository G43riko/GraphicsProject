//
// Created by gabriel on 23.9.2016.
//

#include "RawModel.h"

PointerRawModel createRawModel(GLuint vaoId, GLuint vertexCount){
    return PointerRawModel(new RawModel(vaoId, vertexCount));
}

RawModel::RawModel(GLuint vaoID, GLuint vertexCount){
    this -> vaoID = vaoID;
    this -> vertexCount = vertexCount;
}

GLuint RawModel::getVaoID(void){
    return this -> vaoID;
}

GLuint RawModel::getVertexCount(void) {
    return vertexCount;
}