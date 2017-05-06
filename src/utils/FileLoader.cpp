//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONTENTLOADER_H

#include <src/rendering/Camera.h>
#include "FileLoader.h"

/*
 * TEXT FILES
 */

void ContentLoader::loadTextFile(std::string fileName, std::string *content){
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

/*
 * TEXTURES
 */



CubeImageData * ContentLoader::loadCubeTexture(std::string title){
    CubeImageData * datas = new CubeImageData[6];
    std::vector<std::string> TITLES = {"Right", "Left", "Top", "Bottom", "Back", "Front"};
    for(int i=0 ; i<6 ; i++){
        DEBUG("načitava sa: " << std::string("res/textures/skies/" + title + TITLES[i] + ".png").c_str());
        lodepng::decode(datas[i].data, datas[i].width, datas[i].height, "res/textures/skies/" + title + TITLES[i] + ".png");
    }
    datas[0].title = title;
    return datas;
}

CubeImageData ContentLoader::loadTextureColor(Vector3f color){
    CubeImageData result;
    result.width = 2;
    result.height = 2;
    result.title = color.toString();


    result.data.clear();
    result.data.push_back((unsigned char)color.getX());
    result.data.push_back((unsigned char)color.getY());
    result.data.push_back((unsigned char)color.getZ());
    result.data.push_back(255);
    result.data.push_back((unsigned char)color.getX());
    result.data.push_back((unsigned char)color.getY());
    result.data.push_back((unsigned char)color.getZ());
    result.data.push_back(255);
    result.data.push_back((unsigned char)color.getX());
    result.data.push_back((unsigned char)color.getY());
    result.data.push_back((unsigned char)color.getZ());
    result.data.push_back(255);
    result.data.push_back((unsigned char)color.getX());
    result.data.push_back((unsigned char)color.getY());
    result.data.push_back((unsigned char)color.getZ());
    result.data.push_back(255);

    return result;
}

CubeImageData ContentLoader::loadTexturePNG(std::string fileName){
    CubeImageData result;
    result.title = fileName;
    unsigned error = lodepng::decode(result.data, result.width, result.height, fileName);
    if (error != 0) {
        std::cout << "error [" << fileName << "] " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    return result;
}

/*
 * OBJECTS
 */

PointerMesh ContentLoader::loadOBJ(std::string fileName) {
    std::ifstream ifs(fileName, std::ios::in);

    std::string line;
    std::vector<PointerVertex> vertices = std::vector<PointerVertex>();
    std::vector<Vector2f> textures = std::vector<Vector2f>();
    std::vector<Vector3f> normals = std::vector<Vector3f>();
    VectorUI indices = VectorUI();

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

        PointerVertex v0 = processVertex(vertex1, vertices, indices);
        PointerVertex v1 = processVertex(vertex2, vertices, indices);
        PointerVertex v2 = processVertex(vertex3, vertices, indices);
        calculateTangents(*v0, *v1, *v2, textures);
        std::getline(ifs, line);

    }
    removeUnusedVertices(vertices);

//    if(fileName == "res/models/plane.obj"){
//        printf("vertices size po: %ld\n", vertices.size());
//        for(unsigned int i=0 ; i<vertices.size() ; i++)
//            vertices.at(i) -> show();
////        PRINT("textures: ");
////        for(auto i : textures){
////            i.show();
////        }
//    }
//

    VectorF verticesFinal;
    VectorF uvsFinal;
//    VectorUI indicesFinal;
    VectorF normalsFinal;
    VectorF tangentsFinal;

    convertDataToArrays(vertices, textures, normals, verticesFinal, uvsFinal, normalsFinal, tangentsFinal);
//            printf("x: %f\n", verticesFinal[i]);

//    if(fileName == "res/models/plane.obj"){
//        printf("vertices size nakoniec: %ld\n", vertices.size());
//        for(unsigned int i=0 ; i<vertices.size() ; i++)
//            vertices.at(i) -> show();
//        for(auto i : uvsFinal){
//            printf("uvsFinal: %f\n" , i);
//        }
//    }
    return PointerMesh(new Mesh(verticesFinal, uvsFinal, normalsFinal, tangentsFinal, indices));
    //float furthest = convertDataToArrays(vertices, textures, normals, verticesArray, texturesArray, normalsArray, tangentsArray);
    // ModelData data = new ModelData(verticesArray, texturesArray,
    // normalsArray, tangentsArray, indicesArray,
    // furthest);
}

void ContentLoader::split(const std::string text, char divider, std::vector<std::string>& result) {
    unsigned long i = 0;
    auto pos = text.find(divider);
    while (pos != std::string::npos) {
        result.push_back(text.substr(i, pos-i));
        i = static_cast<int>(++pos);
        pos = text.find(divider, pos);

        if (pos == std::string::npos)
            result.push_back(text.substr(i, text.length()));
    }
}

PointerVertex ContentLoader::processVertex(Vector3f vertex, std::vector<PointerVertex>& vertices, VectorUI& indices) {
    GLuint index = (GLuint)vertex.x - 1;
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

PointerVertex ContentLoader::dealWithAlreadyProcessedVertex(PointerVertex previousVertex, int newTextureIndex, int newNormalIndex, VectorUI& indices, std::vector<PointerVertex>& vertices) {
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

void ContentLoader::removeUnusedVertices(std::vector<PointerVertex>& vertices) {
    for (PointerVertex vertex : vertices) {
        vertex -> averageTangents();
        if (!vertex -> isSet()) {
            vertex -> setTextureIndex(0);
            vertex -> setNormalIndex(0);
        }
    }
}

void ContentLoader::calculateTangents(Vertex & v0, Vertex & v1, Vertex & v2, std::vector<Vector2f> textures) {
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

float ContentLoader::convertDataToArrays(std::vector<PointerVertex> vertices,
                          std::vector<Vector2f> textures,
                          std::vector<Vector3f> normals,
                          VectorF& verticesArray,
                          VectorF& texturesArray,
                          VectorF& normalsArray,
                          VectorF& tangentsArray) {
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

#endif