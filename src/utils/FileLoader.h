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

class ContentLoader {
public:
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
    static void loadTextFile(std::string, std::string *);
    static PointerTexture2D loadTexture(std::string, unsigned int, unsigned int);
    static PointerMesh loadOBJ(std::string fileName) {
        std::ifstream ifs(fileName, std::ios::in);

        std::string line;
        std::vector<Vertex *> vertices = std::vector<Vertex *>();
        std::vector<Vector2f *> textures = std::vector<Vector2f *>();
        std::vector<Vector3f *> normals = std::vector<Vector3f *>();
        std::vector<GLuint> indices = std::vector<GLuint>();

        std::vector<std::string> currentLine;
        while (std::getline(ifs, line)) {
            if (line.find("v ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector3f * vertex = new Vector3f(atof(currentLine.at(1).c_str()),
                                                 atof(currentLine.at(2).c_str()),
                                                 atof(currentLine.at(3).c_str()));
                vertices.push_back(new Vertex(vertices.size(), vertex));

            } else if (line.find("vt ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector2f * texture = new Vector2f(atof(currentLine.at(1).c_str()),
                                                  atof(currentLine.at(2).c_str()));
                textures.push_back(texture);

            } else if (line.find("vn ") == 0) {
                currentLine.clear();
                split(line, ' ', currentLine);
                Vector3f * normal = new Vector3f(atof(currentLine.at(1).c_str()),
                                                 atof(currentLine.at(2).c_str()),
                                                 atof(currentLine.at(3).c_str()));
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
            split(currentLine.at(1), '/', ver1);
            split(currentLine.at(2), '/', ver2);
            split(currentLine.at(3), '/', ver3);

            Vector3f * vertex1 = new Vector3f(atof(ver1.at(0).c_str()), atof(ver1.at(1).c_str()), atof(ver1.at(2).c_str()));
            Vector3f * vertex2 = new Vector3f(atof(ver2.at(0).c_str()), atof(ver2.at(1).c_str()), atof(ver2.at(2).c_str()));;
            Vector3f * vertex3 = new Vector3f(atof(ver3.at(0).c_str()), atof(ver3.at(1).c_str()), atof(ver3.at(2).c_str()));;

            Vertex * v0 = processVertex(vertex1, vertices, indices);
            Vertex * v1 = processVertex(vertex2, vertices, indices);
            Vertex * v2 = processVertex(vertex3, vertices, indices);
            calculateTangents(v0, v1, v2, textures);

            std::getline(ifs, line);
        }
        removeUnusedVertices(vertices);

        std::vector<GLfloat> verticesFinal;
        std::vector<GLfloat> uvsFinal;
        std::vector<GLuint> indicesFinal;
        std::vector<GLfloat> normalsFinal;
        std::vector<GLfloat> tangentsFinal;
        convertDataToArrays(vertices, textures, normals, verticesFinal, uvsFinal, normalsFinal, tangentsFinal);
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
    static Vertex * processVertex(Vector3f * vertex, std::vector<Vertex*>& vertices, std::vector<GLuint>& indices) {
        int index = (int)vertex -> x - 1;
        Vertex * currentVertex = vertices.at(index);
        int textureIndex = (int)vertex -> y - 1;
        int normalIndex = (int)vertex -> z - 1;
        if (!currentVertex -> isSet()) {
            currentVertex -> setTextureIndex(textureIndex);
            currentVertex -> setNormalIndex(normalIndex);
            indices.push_back(index);
            return currentVertex;
        } else {
            return dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
        }
    }
    static Vertex * dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex, int newNormalIndex, std::vector<GLuint>& indices, std::vector<Vertex*>& vertices) {
        if (previousVertex -> hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
            indices.push_back(static_cast<GLuint>(previousVertex -> getIndex()));
            return previousVertex;
        } else {
            Vertex * anotherVertex = previousVertex -> getDuplicateVertex();
            if (anotherVertex != NULL) {
                return dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
            } else {
                Vertex * duplicateVertex = new Vertex(vertices.size(), previousVertex -> getPosition());
                duplicateVertex -> setTextureIndex(newTextureIndex);
                duplicateVertex -> setNormalIndex(newNormalIndex);
                previousVertex -> setDuplicateVertex(duplicateVertex);
                vertices.push_back(duplicateVertex);
                indices.push_back(static_cast<GLuint>(duplicateVertex -> getIndex()));
                return duplicateVertex;
            }

        }
    }
    static void removeUnusedVertices(std::vector<Vertex *>& vertices) {
        /*
        for(auto it = vertices.begin(); it != vertices.end(); ++it) {
            (*it) -> averageTangents();
            if((*it) -> isSet()){
                (*it) -> setTextureIndex(0);
                (*it) -> setNormalIndex(0);
            }
        }
         */
        for (Vertex * vertex : vertices) {
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
            indicesArray[i] = indices.at(i);
        }
        return indicesArray;
    }
    static float convertDataToArrays(std::vector<Vertex *> vertices,
                                     std::vector<Vector2f *> textures,
                                     std::vector<Vector3f *> normals,
                                     std::vector<GLfloat>& verticesArray,
                                     std::vector<GLfloat>& texturesArray,
                                     std::vector<GLfloat>& normalsArray,
                                     std::vector<GLfloat>& tangentsArray) {
        float furthestPoint = 0;
        for (unsigned int i = 0; i < vertices.size(); i++) {
            Vertex * currentVertex = vertices.at(i);
            Vector3f * position = currentVertex -> getPosition();
            Vector2f * textureCoord = textures.at(currentVertex -> getTextureIndex());
            Vector3f * normalVector = normals.at(currentVertex-> getNormalIndex());
            Vector3f tangent = currentVertex -> getAverageTangent();
            //tangent -> show();
            verticesArray.push_back(position -> x);
            verticesArray.push_back(position -> y);
            verticesArray.push_back(position -> z);
            texturesArray.push_back(textureCoord -> x);
            texturesArray.push_back(1 - textureCoord -> y);
            normalsArray.push_back(normalVector -> x);
            normalsArray.push_back(normalVector -> y);
            normalsArray.push_back(normalVector -> z);
            tangentsArray.push_back(tangent.x);
            tangentsArray.push_back(tangent.y);
            tangentsArray.push_back(tangent.z);
        }
        return furthestPoint;
    }

    static void calculateTangents(Vertex * v0, Vertex * v1, Vertex * v2, std::vector<Vector2f *> textures) {
        Vector3f deltaPos1 = *v1 -> getPosition() - *v0 -> getPosition();
        Vector3f deltaPos2 = *v2 -> getPosition() - *v0 -> getPosition();
        Vector2f * uv0 = textures.at(v0 -> getTextureIndex());
        Vector2f * uv1 = textures.at(v1 -> getTextureIndex());
        Vector2f * uv2 = textures.at(v2 -> getTextureIndex());

        Vector2f deltaUv1 = *uv1 - *uv0;
        Vector2f deltaUv2 = *uv2 - *uv0;

        float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
        deltaPos1 *= deltaUv2.y;
        deltaPos2 *= deltaUv1.y;

        Vector3f * tangent = new Vector3f((deltaPos1 - deltaPos2) * r);
        v0 -> addTangent(tangent);
        v1 -> addTangent(tangent);
        v2 -> addTangent(tangent);

    }
};


#endif //GRAPHICSPROJECT_CONTENTLOADER_H


