//
// Created by gabriel on 23.9.2016.
//

#include "Loader.h"

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions){
    GLuint vaoID = createVAO();
    storeDataInAttributeList(0, 3, positions);
    unbindVAO();
    return PointerRawModel(new RawModel(vaoID, (int)positions.size() / 3));
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, std::vector<GLuint> indices){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    unbindVAO();
    return PointerRawModel(new RawModel(vaoID, (int)indices.size()));
}

PointerRawModel Loader::loadToVao(std::vector<GLfloat> positions, std::vector<GLfloat> texts, std::vector<GLuint> indices){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, texts);
    unbindVAO();
    return PointerRawModel(new RawModel(vaoID, (int)indices.size()));
}

PointerRawModel Loader::loadToVao(PointerMesh mesh){
    GLuint vaoID = createVAO();
    bindIndicesBuffer(mesh -> indices);
    storeDataInAttributeList(0, 3, mesh -> vertices);
    storeDataInAttributeList(1, 2, mesh -> uvs);
    storeDataInAttributeList(2, 3, mesh -> normals);
    unbindVAO();
    return PointerRawModel(new RawModel(vaoID, (int)mesh -> indices.size()));
}

void Loader::cleanUp(void){
    for (auto it = vaos.begin(); it != vaos.end(); ++it)
        glDeleteVertexArrays(1, &(*it));
    for (auto it = vbos.begin(); it != vbos.end(); ++it)
        glDeleteBuffers(1, &(*it));
}

GLuint Loader::createVAO(void){
    GLuint vaoID;
    vaos.push_front(vaoID);
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::bindIndicesBuffer(std::vector<GLuint> buffer){
    GLuint vboID;
    vbos.push_front(vboID);
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), GL_STATIC_DRAW);
}



void Loader::storeDataInAttributeList(int attributeNumber, int size, std::vector<GLfloat> buffer){
    GLuint vboID;
    vbos.push_front(vboID);
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO(){
    glBindVertexArray(0);
}