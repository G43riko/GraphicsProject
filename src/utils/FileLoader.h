//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H
#define GRAPHICSPROJECT_CONTENTLOADER_H

#include <string>
#include "Const.h"
#include "Logger.cpp"
#include <fstream>
#include "../rendering/model/Mesh.h"
#include "../rendering/material/Texture2D.h"
#include "Vectors.h"

#include <vector>
#include <GL/glew.h>
#include "Vertex.h"
#include <string.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../static_libs/lodepng.h"
#include "../rendering/material/CubeTexture.h"

class ContentLoader {
public:
    static std::vector<std::string> TITLES;
    static CubeTexture loadCubeTexture(std::string title){
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

        for(int i=0 ; i<6 ; i++){
            unsigned int width;
            unsigned int height;
            std::vector<unsigned char> image;
            /*unsigned error = */lodepng::decode(image, width, height, "res/textures/skies/" + title + TITLES[i] + ".png");
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        return CubeTexture(title, texture_id);
    }
    static PointerTexture2D loadTextureColor(Vector3f color){
        std::vector<unsigned char> image;
        image.clear();
        image.push_back(color.getXuc());
        image.push_back(color.getYuc());
        image.push_back(color.getZuc());
        image.push_back(255);
        image.push_back(color.getXuc());
        image.push_back(color.getYuc());
        image.push_back(color.getZuc());
        image.push_back(255);
        image.push_back(color.getXuc());
        image.push_back(color.getYuc());
        image.push_back(color.getZuc());
        image.push_back(255);
        image.push_back(color.getXuc());
        image.push_back(color.getYuc());
        image.push_back(color.getZuc());
        image.push_back(255);
        return initTexture2D("gabo", image, 2, 2);
    }
    static PointerTexture2D loadTexturePNG(std::string fileName){
        unsigned int width;
        unsigned int height;
        std::vector<unsigned char> image;
        unsigned error = lodepng::decode(image, width, height, fileName);
        if(error != 0) {
            std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        }
        return initTexture2D(fileName, image, width, height);
    }
    static PointerTexture2D initTexture2D(std::string title, std::vector<unsigned char> buffer, int width, int height){
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //TODO ako zistiť či ide o GL_RGBA alebo GL_RGB??
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());

        //ANISOTROPIC
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);

        //MIPMAING
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -2.4f);

        return PointerTexture2D(new Texture2D(title, texture_id, width, height));
    }
    static void loadTextFile(std::string, std::string *);
    static PointerTexture2D loadTexture(std::string, unsigned int, unsigned int);
    static PointerMesh loadOBJ(std::string fileName) {
        std::ifstream ifs(fileName, std::ios::in);

        std::string line;
        std::vector<PointerVertex> vertices = std::vector<PointerVertex>();
        std::vector<Vector2f> textures = std::vector<Vector2f>();
        std::vector<Vector3f> normals = std::vector<Vector3f>();
        std::vector<GLuint> indices = std::vector<GLuint>();

        std::vector<std::string> currentLine;
        while (std::getline(ifs, line)) {
            if (line.find("v ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector3f vertex = Vector3f(atof(currentLine[1].c_str()),
                                           atof(currentLine[2].c_str()),
                                           atof(currentLine[3].c_str()));
                vertices.push_back(PointerVertex(new Vertex(vertices.size(), vertex)));

            } else if (line.find("vt ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector2f texture = Vector2f(atof(currentLine[1].c_str()),
                                            atof(currentLine[2].c_str()));
                textures.push_back(texture);

            } else if (line.find("vn ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector3f normal = Vector3f(atof(currentLine[1].c_str()),
                                           atof(currentLine[2].c_str()),
                                           atof(currentLine[3].c_str()));
                normals.push_back(normal);
            } else if (line.find("f ") == 0) {
                break;
            }
        }
        while (!ifs.eof() && line.find("f ") == 0) {
            currentLine.clear();
            std::vector<std::string> ver1;
            std::vector<std::string> ver2;
            std::vector<std::string> ver3;

            split(line, ' ', currentLine);
            split(currentLine[1], '/', ver1);
            split(currentLine[2], '/', ver2);
            split(currentLine[3], '/', ver3);

            Vector3f vertex1 = Vector3f(atof(ver1[0].c_str()), atof(ver1[1].c_str()), atof(ver1[2].c_str()));
            Vector3f vertex2 = Vector3f(atof(ver2[0].c_str()), atof(ver2[1].c_str()), atof(ver2[2].c_str()));;
            Vector3f vertex3 = Vector3f(atof(ver3[0].c_str()), atof(ver3[1].c_str()), atof(ver3[2].c_str()));;

            if(fileName == "res/models/axe.obj" && false) {
                vertex1.show();
                vertex2.show();
                vertex3.show();
            }

            PointerVertex v0 = processVertex(vertex1, vertices, indices);
            PointerVertex v1 = processVertex(vertex2, vertices, indices);
            PointerVertex v2 = processVertex(vertex3, vertices, indices);
            calculateTangents(*v0, *v1, *v2, textures);
            std::getline(ifs, line);
        }
        removeUnusedVertices(vertices);

        std::vector<GLfloat> verticesFinal;
        std::vector<GLfloat> uvsFinal;
        std::vector<GLuint> indicesFinal;
        std::vector<GLfloat> normalsFinal;
        std::vector<GLfloat> tangentsFinal;

        if(fileName == "res/models/axe.obj" && false){
            for(int i=0 ; i<vertices.size() ; i++)
                printf("x: %f\n", vertices.at(i) -> position.x);
        }
        convertDataToArrays(vertices, textures, normals, verticesFinal, uvsFinal, normalsFinal, tangentsFinal);
//            printf("x: %f\n", verticesFinal[i]);
        return PointerMesh(new Mesh(verticesFinal, uvsFinal, normalsFinal, tangentsFinal, indices));
        //float furthest = convertDataToArrays(vertices, textures, normals, verticesArray, texturesArray, normalsArray, tangentsArray);
        // ModelData data = new ModelData(verticesArray, texturesArray,
        // normalsArray, tangentsArray, indicesArray,
        // furthest);
    }
private:
    static void split(const std::string s, char delim, std::vector<std::string>& v) {
        auto i = 0;
        auto pos = s.find(delim);
        while (pos != std::string::npos) {
            v.push_back(s.substr(i, pos-i));
            i = static_cast<int>(++pos);
            pos = s.find(delim, pos);

            if (pos == std::string::npos)
                v.push_back(s.substr(i, s.length()));
        }
    }
    static PointerVertex processVertex(Vector3f vertex, std::vector<PointerVertex>& vertices, std::vector<GLuint>& indices) {
        int index = (int)vertex.x - 1;
        PointerVertex currentVertex = vertices[index];
        int textureIndex = (int)vertex.y - 1;
        int normalIndex = (int)vertex.z - 1;
        if (!currentVertex -> isSet()) {
            currentVertex -> setTextureIndex(textureIndex);
            currentVertex -> setNormalIndex(normalIndex);
            indices.push_back(index);
            return currentVertex;
        } else {
            return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
        }
    }
    static PointerVertex dealWithAlreadyProcessedVertex(PointerVertex previousVertex, int newTextureIndex, int newNormalIndex, std::vector<GLuint>& indices, std::vector<PointerVertex>& vertices) {
        if (previousVertex -> hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
            indices.push_back(static_cast<GLuint>(previousVertex -> getIndex()));
            return previousVertex;
        } else {
            PointerVertex anotherVertex = previousVertex -> getDuplicateVertex();
            if (anotherVertex != NULL) {
                return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
            } else {
                PointerVertex duplicateVertex = PointerVertex(new Vertex(vertices.size(), previousVertex -> getPosition()));
                duplicateVertex -> setTextureIndex(newTextureIndex);
                duplicateVertex -> setNormalIndex(newNormalIndex);
                previousVertex -> setDuplicateVertex(duplicateVertex);
                vertices.push_back(duplicateVertex);
                indices.push_back(static_cast<GLuint>(duplicateVertex -> getIndex()));
                return duplicateVertex;
            }

        }
    }
    static void removeUnusedVertices(std::vector<PointerVertex>& vertices) {
        for (PointerVertex vertex : vertices) {
            vertex -> averageTangents();
            if (!vertex -> isSet()) {
                vertex -> setTextureIndex(0);
                vertex -> setNormalIndex(0);
            }
        }
    }
    static int* convertIndicesListToArray(std::vector<int> indices) {
        int* indicesArray = new int[indices.size()];
        for (unsigned long i = 0; i < indices.size(); i++) {
            indicesArray[i] = indices[i];
        }
        return indicesArray;
    }
    static float convertDataToArrays(std::vector<PointerVertex> vertices,
                                     std::vector<Vector2f> textures,
                                     std::vector<Vector3f> normals,
                                     std::vector<GLfloat>& verticesArray,
                                     std::vector<GLfloat>& texturesArray,
                                     std::vector<GLfloat>& normalsArray,
                                     std::vector<GLfloat>& tangentsArray) {
        float furthestPoint = 0;
        for (unsigned int i = 0; i < vertices.size(); i++) {
            PointerVertex currentVertex = vertices[i];
            Vector3f position = currentVertex -> getPosition();
            Vector2f textureCoord = textures[currentVertex -> getTextureIndex()];
            Vector3f normalVector = normals[currentVertex-> getNormalIndex()];
            Vector3f tangent = currentVertex -> getAverageTangent();
            //tangent -> show();
            verticesArray.push_back(position.x);
            verticesArray.push_back(position.y);
            verticesArray.push_back(position.z);
            texturesArray.push_back(textureCoord.x);
            texturesArray.push_back(1 - textureCoord.y);
            normalsArray.push_back(normalVector.x);
            normalsArray.push_back(normalVector.y);
            normalsArray.push_back(normalVector.z);
            tangentsArray.push_back(tangent.x);
            tangentsArray.push_back(tangent.y);
            tangentsArray.push_back(tangent.z);
        }
        return furthestPoint;
    }

    static void calculateTangents(Vertex & v0, Vertex & v1, Vertex & v2, std::vector<Vector2f> textures) {
        Vector3f deltaPos1 = v1.getPosition() - v0.getPosition();
        Vector3f deltaPos2 = v2.getPosition() - v0.getPosition();
        Vector2f uv0 = textures[v0.getTextureIndex()];
        Vector2f uv1 = textures[v1.getTextureIndex()];
        Vector2f uv2 = textures[v2.getTextureIndex()];

        Vector2f deltaUv1 = uv1 - uv0;
        Vector2f deltaUv2 = uv2 - uv0;

        float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
        deltaPos1 *= deltaUv2.y;
        deltaPos2 *= deltaUv1.y;

        Vector3f tangent = Vector3f((deltaPos1 - deltaPos2) * r);
        v0.addTangent(tangent);
        v1.addTangent(tangent);
        v2.addTangent(tangent);

    }
};

#endif //GRAPHICSPROJECT_CONTENTLOADER_H


