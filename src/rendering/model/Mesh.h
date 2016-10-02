//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_MESH_H
#define GRAPHICSPROJECT_MESH_H

#include <GL/glew.h>
#include <vector>
#include <iostream>

class Mesh {
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> uvs;
        std::vector<GLuint> indices;
        std::vector<GLfloat> normals;
        static Mesh * plane;
        static Mesh * cube;
        void show(void);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
};


#endif //GRAPHICSPROJECT_MESH_H
