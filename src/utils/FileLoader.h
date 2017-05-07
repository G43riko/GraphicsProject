//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H
#define GRAPHICSPROJECT_CONTENTLOADER_H

#include <string>
#include "Const.h"
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
#include "GTypes.h"
//#include <src/static_libs/tiny_obj_loader.cpp>



class ContentLoader {
public:
    static CubeImageData * loadCubeTexture(std::string title);
    static CubeImageData loadTextureColor(Vector3f color);
    static CubeImageData loadTexturePNG(std::string fileName);
    static PointerMesh loadOBJ(std::string fileName);
    inline static void loadShader(std::string fileName, std::string * content){

        std::ifstream ifs(SHADERS_FOLDER + fileName, std::ios::in);
        std::string line = "";

        if(ifs.is_open()) {
            while(!ifs.eof()) {
                std::getline(ifs, line);
                if(START_WITH(line, INCLUDE_IDENTIFICATOR " ")){
                    loadShader(line.substr(9) + EXTENSION_GLSL, content);
                }
                else{
                    content -> append(line + "\n");
                }
            }
            ifs.close();
            return;
        }
        ERROR(ERROR_MISSING_FILE SHADERS_FOLDER + fileName);
    }
    inline static void loadTextFile(std::string fileName, std::string *content){
        std::ifstream ifs(fileName, std::ios::in);
        std::string line = "";

        if(ifs.is_open()) {
            while(!ifs.eof()) {
                std::getline(ifs, line);
                content -> append(line + "\n");
            }
            ifs.close();
            return;
        }
        ERROR(ERROR_MISSING_FILE + fileName);
    }
private:

    static void split(const std::string text, char divider, VectorS& result);

    static PointerVertex processVertex(Vector3f vertex, std::vector<PointerVertex>& vertices, VectorUI& indices);

    static void removeUnusedVertices(std::vector<PointerVertex>& vertices);


    static void calculateTangents(Vertex & v0, Vertex & v1, Vertex & v2, VectorV2 textures);

    static PointerVertex dealWithAlreadyProcessedVertex(PointerVertex previousVertex,
                                                        int newTextureIndex,
                                                        int newNormalIndex,
                                                        VectorUI& indices,
                                                        std::vector<PointerVertex>& vertices);

    static float convertDataToArrays(std::vector<PointerVertex> vertices,
                                     VectorV2 textures,
                                     VectorV3 normals,
                                     VectorF& verticesArray,
                                     VectorF& texturesArray,
                                     VectorF& normalsArray,
                                     VectorF& tangentsArray);


    /*
     * DEPRECATED
     */
    /*
    static PointerTexture2D loadTexture(std::string, unsigned int, unsigned int);
     */
};

#endif //GRAPHICSPROJECT_CONTENTLOADER_H


