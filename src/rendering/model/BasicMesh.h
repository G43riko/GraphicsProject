//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_MESH2_H
#define GAMEENGINE_MESH2_H

#include <src/utils/GTypes.h>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <src/rendering/shader/BasicShader.h>

struct SimpleVertex{
    VectorV3 position;
    VectorV3 normal;
    VectorV2 texCoords;
};
struct SimpleTexture {
    GLuint id;
    std::string type;
};
class SimpleMesh{
public:
    /*  Mesh Data  */
    std::vector<SimpleVertex> vertices;
    VectorUI indices;
    std::vector<SimpleTexture> textures;
    /*  Functions  */
    SimpleMesh(std::vector<SimpleVertex> vertices, VectorUI indices, std::vector<SimpleTexture> textures){
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        this->setupMesh();
    };
    void Draw(BasicShader * shader){
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for(GLuint i = 0; i < this -> textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
            // Retrieve texture number (the N in diffuse_textureN)
            std::stringstream ss;
            std::string number;
            std::string name = this->textures[i].type;
            if(name == "texture_diffuse")
                ss << diffuseNr++; // Transfer GLuint to stream
            else if(name == "texture_specular")
                ss << specularNr++; // Transfer GLuint to stream
            number = ss.str();
            shader ->updateUniformf("material." + name + number, i);
            glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        // Draw mesh
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    };
private:
    /*  Render data  */
    GLuint VAO, VBO, EBO;
    /*  Functions    */
    void setupMesh(){
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
                     &this->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
                     &this->indices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (GLvoid*)0);
        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(SimpleVertex, normal));
        // Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(SimpleVertex, texCoords));

        glBindVertexArray(0);
    };
};

#endif //GAMEENGINE_MESH2_H
