//
// Created by gabriel on 25.9.2016.
//

#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLfloat> textureCoors, std::vector<GLuint> indices){
    this -> vertices = vertices;
    this -> textureCoors = textureCoors;
    this -> indices = indices;
}

Mesh * Mesh::plane = new Mesh({-0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f},
                              { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},{ 0, 1, 3, 3, 1, 2});

Mesh * Mesh::cube = new Mesh({-0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,
                              -0.5f,0.5f,0.5f,-0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                              0.5f,0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,0.5f,
                              -0.5f,0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,
                              -0.5f,0.5f,0.5f,-0.5f,0.5f,-0.5f,0.5f,0.5f,-0.5f,0.5f,0.5f,0.5f,
                              -0.5f,-0.5f,0.5f,-0.5f,-0.5f,-0.5f,0.5f,-0.5f,-0.5f,0.5f,-0.5f,0.5f},
                             { 0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,
                               0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0},
                             { 0,1,3,3,1,2,4,5,7,7,5,6,8,9,11,11,9,10,12,13,
                               15,15,13,14,16,17,19,19,17,18,20,21,23,23,21,22});