//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RAWMODEL_H
#define GRAPHICSPROJECT_RAWMODEL_H

#include <GL/glew.h>
#include <memory>
#include <src/utils/GTypes.h>

class RawModel{
private:
    const GLuint vaoID;
    const GLuint vertexCount;
    const GLenum renderType;
public:
    inline RawModel(const GLint& id, const GLint& count, GLenum type = GL_TRIANGLES) :
            vaoID(id),
            vertexCount(count),
            renderType(type){};
    inline GLuint getVaoID(void) const{return this -> vaoID; }
    inline GLuint getVertexCount(void) const{return vertexCount; }
    inline GLenum getRenderType(void) const{return renderType; }
};

inline PointerRawModel createRawModel(GLuint vaoId, GLuint vertexCount, GLenum type = GL_TRIANGLES){
    return PointerRawModel(new RawModel(vaoId, vertexCount, type));
}




#endif //GRAPHICSPROJECT_RAWMODEL_H
