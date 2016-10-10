//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RAWMODEL_H
#define GRAPHICSPROJECT_RAWMODEL_H

#include <GL/glew.h>
#include <memory>

class RawModel{
private:
    GLuint vaoID;
    GLuint vertexCount;
public:
    RawModel(GLuint, GLuint);
    GLuint getVaoID(void);
    GLuint getVertexCount(void);
};
typedef std::shared_ptr<RawModel> PointerRawModel;


#endif //GRAPHICSPROJECT_RAWMODEL_H
