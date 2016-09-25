//
// Created by gabriel on 23.9.2016.
//

#ifndef GRAPHICSPROJECT_LOADER_H
#define GRAPHICSPROJECT_LOADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../rendering/model/RawModel.h"
#include "../rendering/model/Mesh.h"
#include <vector>
#include <list>
#include <iostream>

class Loader {
    public:
        RawModel * loadToVao(std::vector<GLfloat>);
        RawModel * loadToVao(std::vector<GLfloat>, std::vector<GLuint>);
        RawModel * loadToVao(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);

        RawModel * loadToVao(Mesh *);

        void cleanUp(void);
private:
    std::list<GLuint> vaos;
    std::list<GLuint> vbos;
    GLuint createVAO(void);
    void bindIndicesBuffer(std::vector<GLuint>);
    void storeDataInAttributeList(int, int, std::vector<GLfloat>);
    void unbindVAO(void);

    template <typename T> void showBufferData(int size, GLuint id, GLuint type = GL_ARRAY_BUFFER){
        T * target = new T[size * sizeof(T)];
        glBindBuffer(type, id);
        glGetBufferSubData(type, 0, size * sizeof(T), target);
        std::cout << "načítalo sa " << size << " veci: "<< std::endl;
        for(int i=0 ; i<size ; i++)
            std::cout << target[i] << " ";
        std::cout << std::endl;
    }
};

#endif //GRAPHICSPROJECT_LOADER_H
