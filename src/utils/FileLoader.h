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
//#include <src/static_libs/tiny_obj_loader.cpp>

class ContentLoader {
public:
    static std::map<std::string, PointerTexture2D> loadedTestures;
    static std::vector<std::string> TITLES;
    static PointerCubeTexture loadCubeTexture(std::string title);
    static PointerTexture2D loadTextureColor(Vector3f color);
    static PointerTexture2D loadTexturePNG(std::string fileName);
    static PointerMesh loadOBJ(std::string fileName);
    static void loadTextFile(std::string, std::string *);
//    static inline PointerMesh loadObj(std::string fileName){
//        std::string inputfile = "cornell_box.obj";
//        tinyobj::attrib_t attrib;
//        std::vector<tinyobj::shape_t> shapes;
//        std::vector<tinyobj::material_t> materials;
//
//        std::string err;
//        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
//
//        if (!err.empty()) { // `err` may contain warning message.
//            std::cerr << err << std::endl;
//        }
//
//        if (!ret) {
//            exit(1);
//        }
//
//        for (size_t s = 0; s < shapes.size(); s++) {
//            // Loop over faces(polygon)
//            size_t index_offset = 0;
//            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
//                int fv = shapes[s].mesh.num_face_vertices[f];
//                printf("vertices: %d\n", fv);
//                // Loop over vertices in the face.
//                for (size_t v = 0; v < fv; v++) {
//                    // access to vertex
//                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
//                    float vx = attrib.vertices[3*idx.vertex_index+0];
//                    float vy = attrib.vertices[3*idx.vertex_index+1];
//                    float vz = attrib.vertices[3*idx.vertex_index+2];
//                    float nx = attrib.normals[3*idx.normal_index+0];
//                    float ny = attrib.normals[3*idx.normal_index+1];
//                    float nz = attrib.normals[3*idx.normal_index+2];
//                    float tx = attrib.texcoords[2*idx.texcoord_index+0];
//                    float ty = attrib.texcoords[2*idx.texcoord_index+1];
//                }
//                index_offset += fv;
//                // per-face material
//                shapes[s].mesh.material_ids[f];
//            }
//        }
//    }
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


