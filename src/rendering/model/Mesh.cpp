//
// Created by gabriel on 25.9.2016.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLuint> indices){
    this -> vertices = vertices;
    this -> uvs = uvs;
    this -> indices = indices;
}
Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLfloat> normals, std::vector<GLuint> indices){
    this -> vertices = vertices;
    this -> uvs = uvs;
    this -> normals = normals;
    this -> indices = indices;
}
Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> uvs, std::vector<GLfloat> normals, std::vector<GLfloat> tangents, std::vector<GLuint> indices){
    this -> vertices = vertices;
    this -> uvs = uvs;
    this -> normals = normals;
    this -> indices = indices;
    this -> tangents = tangents;
}

std::vector<GLfloat> Mesh::getVertices(void){
    return vertices;
}
std::vector<GLfloat> Mesh::getTangents(void){
    return tangents;
}
std::vector<GLfloat> Mesh::getNormals(void){
    return normals;
}
std::vector<GLfloat> Mesh::getUvs(void){
    return uvs;
}
std::vector<GLuint> Mesh::getIndices(void){
    return indices;
}

void Mesh::show(void){
    std::cout << "vertices: " << std::endl;
    for(auto i : vertices)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "uvs: " << std::endl;
    for(auto i : uvs)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "normals: " << std::endl;
    for(auto i : normals)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "tangents: " << std::endl;
    for(auto i : tangents)
        std::cout << i << " ";
    std::cout << std::endl;
    std::cout << "indices: " << std::endl;
    for(auto i : indices)
        std::cout << i << " ";
    std::cout << std::endl;
}

PointerMesh Mesh::plane = PointerMesh(new Mesh({-1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
                                               { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},{ 0, 1, 3, 3, 1, 2}));

PointerMesh Mesh::cube = PointerMesh(new Mesh({-0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,
                                               -0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                                                0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                                               -0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,
                                               -0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,
                                               -0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f},
                                              { 0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,
                                                0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0},
                                              { 0,1,3,3,1,2,4,5,7,7,5,6,8,9,11,11,9,10,12,13,
                                                15,15,13,14,16,17,19,19,17,18,20,21,23,23,21,22}));