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
        std::vector<GLfloat> tangents;
        std::vector<GLfloat> normals;
        std::vector<GLuint> indices;
        std::vector<GLfloat> uvs;
    public:
        static PointerMesh plane;
        static PointerMesh cube;
        void show(void);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLuint>);
        Mesh(std::vector<GLfloat>, std::vector<GLfloat>, std::vector<GLfloat>,std::vector<GLfloat>, std::vector<GLuint>);


    inline std::vector<GLfloat> getVertices(void){ return vertices; }
    inline std::vector<GLfloat> getTangents(void){ return tangents; }
    inline std::vector<GLfloat> getNormals(void){ return normals; }
    inline std::vector<GLuint> getIndices(void){ return indices; }
    inline std::vector<GLfloat> getUvs(void){ return uvs; }

};

#endif //GRAPHICSPROJECT_MESH_H
