//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_LOADER_H
#define GRAPHICSPROJECT_LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../rendering/model/RawModel.cpp"
#include "../rendering/model/Mesh.h"
#include <vector>
#include <list>
#include <iostream>

class Loader {
    public:
        RawModel * loadToVao(std::vector<GLfloat> positions){
            GLuint vaoID = createVAO();
            storeDataInAttributeList(0, 3, positions);
            unbindVAO();
            return new RawModel(vaoID, (int)positions.size() / 3);
        }
        RawModel * loadToVao(std::vector<GLfloat> positions, std::vector<GLuint> indices){
            GLuint vaoID = createVAO();
            bindIndicesBuffer(indices);
            storeDataInAttributeList(0, 3, positions);
            unbindVAO();
            return new RawModel(vaoID, (int)indices.size());
        }
        RawModel * loadToVao(std::vector<GLfloat> positions, std::vector<GLfloat> texts, std::vector<GLuint> indices){
            GLuint vaoID = createVAO();
            bindIndicesBuffer(indices);
            storeDataInAttributeList(0, 3, positions);
            storeDataInAttributeList(1, 2, texts);
            unbindVAO();
            return new RawModel(vaoID, (int)indices.size());
        }

        RawModel * loadToVao(Mesh * mesh){
            GLuint vaoID = createVAO();
            bindIndicesBuffer(mesh -> indices);
            storeDataInAttributeList(0, 3, mesh -> vertices);
            storeDataInAttributeList(1, 2, mesh -> textureCoors);
            unbindVAO();
            return new RawModel(vaoID, (int)mesh -> indices.size());
        }

        void cleanUp(){
            for (std::list<GLuint>::iterator it = vaos.begin(); it != vaos.end(); ++it)
                glDeleteVertexArrays(1, &(*it));
            for (std::list<GLuint>::iterator it = vbos.begin(); it != vbos.end(); ++it)
                glDeleteBuffers(1, &(*it));
        }
private:
    std::list<GLuint> vaos;
    std::list<GLuint> vbos;
    GLuint createVAO(){
        GLuint vaoID;
        vaos.push_front(vaoID);
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        return vaoID;
    }

    void bindIndicesBuffer(std::vector<GLuint> buffer){
        GLuint vboID;
        vbos.push_front(vboID);
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), GL_STATIC_DRAW);
    }

    template <typename T> void showBufferData(int size, GLuint id, GLuint type = GL_ARRAY_BUFFER){
        T * target = new T[size * sizeof(T)];
        glBindBuffer(type, id);
        glGetBufferSubData(type, 0, size * sizeof(T), target);
        std::cout << "načítalo sa " << size << " veci: "<< std::endl;
        for(int i=0 ; i<size ; i++)
            std::cout << target[i] << " ";
        std::cout << std::endl;
    }

    void storeDataInAttributeList(int attributeNumber, int size, std::vector<GLfloat> buffer){
        GLuint vboID;
        vbos.push_front(vboID);
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, size, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void unbindVAO(){
        glBindVertexArray(0);
    }
};

#endif //GRAPHICSPROJECT_LOADER_H
