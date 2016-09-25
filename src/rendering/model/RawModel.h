//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RAWMODEL_H
#define GRAPHICSPROJECT_RAWMODEL_H

#include <GL/glew.h>

class RawModel{
private:
    GLuint vaoID;
    GLuint vertexCount;
public:
    RawModel(GLuint vaoID, GLuint vertexCount){
        this -> vaoID = vaoID;
        this -> vertexCount = vertexCount;
    }

    GLuint getVaoID(){
        return this -> vaoID;
    }

    GLuint getVertexCount() {
        return vertexCount;
    }

};

#endif //GRAPHICSPROJECT_RAWMODEL_H
