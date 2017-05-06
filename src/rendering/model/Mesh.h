//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_MESH_H
#define GRAPHICSPROJECT_MESH_H

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <memory>
#include <src/utils/Vectors.h>
#include <src/utils/GTypes.h>


class Mesh {
private:
    VectorF vertices;
    VectorF tangents;
    VectorF normals;
    VectorUI indices;
    VectorF uvs;
public:
    inline Mesh(VectorF vertices, VectorUI indices){
        this -> vertices    = vertices;
        this -> indices     = indices;
    }
    inline Mesh(VectorF vertices, VectorF uvs, VectorUI indices){
        this -> vertices    = vertices;
        this -> indices     = indices;
        this -> uvs         = uvs;
    }
    inline Mesh(VectorF vertices, VectorF uvs, VectorF normals, VectorUI indices){
        this -> vertices    = vertices;
        this -> normals     = normals;
        this -> indices     = indices;
        this -> uvs         = uvs;
    }
    inline Mesh(VectorF vertices, VectorF uvs, VectorF normals, VectorF tangents, VectorUI indices){
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


    inline VectorF getVertices(void) const{return vertices; }
    inline VectorF getTangents(void) const{return tangents; }
    inline VectorF getNormals(void) const{return normals; }
    inline VectorUI getIndices(void) const{return indices; }
    inline VectorF getUvs(void) const{return uvs; }

};

#endif //GRAPHICSPROJECT_MESH_H
