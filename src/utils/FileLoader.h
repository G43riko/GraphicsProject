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
#include <map>
#include "../static_libs/lodepng.h"
#include "../rendering/material/CubeTexture.h"

class ContentLoader {
public:
    static std::map<std::string, PointerTexture2D> loadedTestures;
    static std::vector<std::string> TITLES;
    static PointerCubeTexture loadCubeTexture(std::string title);
    static PointerTexture2D loadTextureColor(Vector3f color);
    static PointerTexture2D loadTexturePNG(std::string fileName);
    static PointerMesh loadOBJ(std::string fileName);
    static void loadTextFile(std::string, std::string *);
private:
    static PointerTexture2D initTexture2D(std::string title, std::vector<unsigned char> buffer, int width, int height);

    static void split(const std::string text, char divider, std::vector<std::string>& result);

    static PointerVertex processVertex(Vector3f vertex, std::vector<PointerVertex>& vertices, std::vector<GLuint>& indices);

    static void removeUnusedVertices(std::vector<PointerVertex>& vertices);


    static void calculateTangents(Vertex & v0, Vertex & v1, Vertex & v2, std::vector<Vector2f> textures);

    static PointerVertex dealWithAlreadyProcessedVertex(PointerVertex previousVertex,
                                                        int newTextureIndex,
                                                        int newNormalIndex,
                                                        std::vector<GLuint>& indices,
                                                        std::vector<PointerVertex>& vertices);

    static float convertDataToArrays(std::vector<PointerVertex> vertices,
                                     std::vector<Vector2f> textures,
                                     std::vector<Vector3f> normals,
                                     std::vector<GLfloat>& verticesArray,
                                     std::vector<GLfloat>& texturesArray,
                                     std::vector<GLfloat>& normalsArray,
                                     std::vector<GLfloat>& tangentsArray);


    /*
     * DEPRECATED
     */
    /*
    static PointerTexture2D loadTexture(std::string, unsigned int, unsigned int);
     */
};

#endif //GRAPHICSPROJECT_CONTENTLOADER_H


