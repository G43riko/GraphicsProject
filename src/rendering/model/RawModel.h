//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_RAWMODEL_H
#define GRAPHICSPROJECT_RAWMODEL_H

#include <GL/glew.h>
#include <memory>

class RawModel{
private:
    const GLuint vaoID;
    const GLuint vertexCount;
public:
    inline RawModel(const GLint& vaoID, const GLint& vertexCount) : vaoID(vaoID), vertexCount(vertexCount){};
    inline GLuint getVaoID(void) const{return this -> vaoID; }
    inline GLuint getVertexCount(void) const{return vertexCount; }
};
typedef std::shared_ptr<RawModel> PointerRawModel;

inline PointerRawModel createRawModel(GLuint vaoId, GLuint vertexCount){
    return PointerRawModel(new RawModel(vaoId, vertexCount));
}




#endif //GRAPHICSPROJECT_RAWMODEL_H
