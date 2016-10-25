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
    private:
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> uvs;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> tangents;
        std::vector<GLuint> indices;
    public:
        static PointerMesh plane;
        static PointerMesh cube;
        void show(void);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>,std::vector<GLfloat>, std::vector<GLuint>);

        std::vector<GLfloat> getVertices(void);
        std::vector<GLfloat> getTangents(void);
        std::vector<GLfloat> getNormals(void);
        std::vector<GLfloat> getUvs(void);
        std::vector<GLuint> getIndices(void);
};

#endif //GRAPHICSPROJECT_MESH_H
