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

    inline Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLuint> indices){
        this -> vertices    = vertices;
        this -> indices     = indices;
        this -> uvs         = uvs;
    }
    inline Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLfloat> normals, std::vector<GLuint> indices){
        this -> vertices    = vertices;
        this -> normals     = normals;
        this -> indices     = indices;
        this -> uvs         = uvs;
    }
    inline Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLfloat> normals, std::vector<GLfloat> tangents, std::vector<GLuint> indices){
        this -> vertices    = vertices;
        this -> normals     = normals;
        this -> indices     = indices;
        this -> tangents    = tangents;
        this -> uvs         = uvs;
    }
    inline void show(void) const{
        std::cout << "vertices: " << std::endl;
        for(auto i : vertices){
            std::cout << i << " ";
        }
        std::cout << std::endl << "uvs: " << std::endl;
        for(auto i : uvs){
            std::cout << i << " ";
        }
        std::cout << std::endl << "normals: " << std::endl;
        for(auto i : normals){
            std::cout << i << " ";
        }
        std::cout << std::endl << "tangents: " << std::endl;
        for(auto i : tangents){
            std::cout << i << " ";
        }
        std::cout << std::endl << "indices: " << std::endl;
        for(auto i : indices){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }


    inline std::vector<GLfloat> getVertices(void) const{return vertices; }
    inline std::vector<GLfloat> getTangents(void) const{return tangents; }
    inline std::vector<GLfloat> getNormals(void) const{return normals; }
    inline std::vector<GLuint> getIndices(void) const{return indices; }
    inline std::vector<GLfloat> getUvs(void) const{return uvs; }

};

#endif //GRAPHICSPROJECT_MESH_H
