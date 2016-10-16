//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_MESH_H
#define GRAPHICSPROJECT_MESH_H

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <memory>
class Mesh;

typedef std::shared_ptr<Mesh> PointerMesh;

class Mesh {
    public:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> uvs;
        std::vector<GLuint> indices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> tangents;
        static PointerMesh plane;
        static PointerMesh cube;
        void show(void);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>,std::vector<GLfloat>, std::vector<GLuint>);
};

#endif //GRAPHICSPROJECT_MESH_H
