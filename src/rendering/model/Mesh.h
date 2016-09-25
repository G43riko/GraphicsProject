//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_MESH_H
#define GRAPHICSPROJECT_MESH_H

#include <GL/glew.h>
#include <vector>

class Mesh {
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> textureCoors;
        std::vector<GLuint> indices;
        static Mesh * plane;
        static Mesh * cube;
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
};


#endif //GRAPHICSPROJECT_MESH_H
