//
// Created by gabriel on 23.9.2016.
//

#include "Loader.h"

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions){
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, 3, positions);
    unbindVAO();
    return createRawModel(vaoID, (GLuint)positions.size() / 3);
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, std::vector<GLuint> indices){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    unbindVAO();
    return createRawModel(vaoID, (int)indices.size());
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, std::vector<GLfloat> texts, std::vector<GLfloat> normals, std::vector<GLuint> indices){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, texts);
    storeDataInAttributeList(2, 3, normals);
    unbindVAO();
    return createRawModel(vaoID, (GLuint)indices.size());
}
PointerRawModel Loader::loadToVaoA(GLfloat * vertices,GLfloat * textures, GLfloat * normals, GLuint * indices){
    GLuint vaoID = createVAO();
    bindIndicesBufferArray(indices);
    storeDataInAttributeArray(0, 3, vertices);
    storeDataInAttributeArray(1, 2, textures);
    storeDataInAttributeArray(2, 3, normals);
    unbindVAO();
    return createRawModel(vaoID, sizeof(indices) / sizeof(GLuint));
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, std::vector<GLfloat> texts, std::vector<GLuint> indices){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, texts);
    unbindVAO();
    return createRawModel(vaoID, (int)indices.size());
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, int dimensions) {
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, dimensions, positions);
    unbindVAO();
    return createRawModel(vaoID, (GLuint)(positions.size() / dimensions));
}

PointerRawModel Loader::loadToVao(PointerMesh mesh){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(mesh -> getIndices());
    storeDataInAttributeList(0, 3, mesh -> getVertices());
    storeDataInAttributeList(1, 2, mesh -> getUvs());
    storeDataInAttributeList(2, 3, mesh -> getNormals());
    //storeDataInAttributeList(3, 3, mesh -> getTangents());
    unbindVAO();
    return createRawModel(vaoID, (GLuint)mesh -> getIndices().size());
}

void Loader::cleanUp(void){
    for(GLuint vao : vaos){
        glDeleteVertexArrays(1, &vao);
    }
    for(GLuint vbo : vbos){
        glDeleteBuffers(1, &vbo);
    }
}

GLuint Loader::createVAO(void){
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    vaos.push_front(vaoID);
    return vaoID;
}

void Loader::bindIndicesBuffer(std::vector<GLuint> buffer){
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), GL_STATIC_DRAW);
    vbos.push_front(vboID);
}
void Loader::bindIndicesBufferArray(GLuint * buffer){
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    vbos.push_front(vboID);
}



void Loader::storeDataInAttributeArray(GLuint attributeNumber, int size, GLfloat * buffer){
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_front(vboID);
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, int size, std::vector<GLfloat> buffer){
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_front(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO(){
    glBindVertexArray(0);
}