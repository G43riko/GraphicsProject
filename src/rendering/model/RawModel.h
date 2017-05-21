//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RAWMODEL_H
#define GRAPHICSPROJECT_RAWMODEL_H

#include <GL/glew.h>
#include <memory>
#include <src/utils/GTypes.h>

class RawModel{
    const GLuint _vaoID;
    const GLuint _vertexCount;
    const GLenum _renderType;

    inline RawModel(const GLint id, const GLint count, const GLenum type = GL_TRIANGLES) :
            _vaoID(id),
            _vertexCount(count),
            _renderType(type){};
public:
    inline GLuint getVaoID(void) const{return _vaoID; }
    inline GLuint getVertexCount(void) const{return _vertexCount; }
    inline GLenum getRenderType(void) const{return _renderType; }

    inline static PointerRawModel create(GLuint vaoId, GLuint vertexCount, GLenum type = GL_TRIANGLES){
        return PointerRawModel(new RawModel(vaoId, vertexCount, type));
    }

};





#endif //GRAPHICSPROJECT_RAWMODEL_H
