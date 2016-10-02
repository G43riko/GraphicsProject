//
// Created by gabriel on 29.9.2016.
//

#ifndef GRAPHICSPROJECT_VERTEX_H
#define GRAPHICSPROJECT_VERTEX_H

#include "Vectors.h"
#include <vector>

class Vertex {
    private:
        int NO_INDEX = -1;

        int textureIndex = NO_INDEX;
        int normalIndex = NO_INDEX;
        Vertex * duplicateVertex = NULL;
        long unsigned int index;
        float length;
        std::vector<Vector3f *> tangents = std::vector<Vector3f *>();
        Vector3f * averagedTangent = new Vector3f(0, 0, 0);
    public:
        Vector3f * position;
        Vertex(long unsigned int index,Vector3f * position){
            this -> index = index;
            this -> position = position;
            this -> length = position -> getLength();
        }
    void show(){
        position -> show();
    }
    void addTangent(Vector3f * tangent){
        tangents.push_back(tangent);
    }

    void averageTangents(){
        if(tangents.size() == 0){
            return;
        }
        for(Vector3f * tangent : tangents){
            averagedTangent -> add(tangent);
        }
        averagedTangent -> normalize();
    }

    Vector3f * getAverageTangent(){
        return averagedTangent;
    }

    long unsigned int getIndex(){
        return index;
    }

    float getLength(){
        return length;
    }

    bool isSet(){
        return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
    }

    bool hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther){
        return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
    }

    void setTextureIndex(int textureIndex){
        this -> textureIndex = textureIndex;
    }

    void setNormalIndex(int normalIndex){
        this -> normalIndex = normalIndex;
    }

    Vector3f * getPosition() {
        return position;
    }

    int getTextureIndex() {
        return textureIndex;
    }

    int getNormalIndex() {
        return normalIndex;
    }

    Vertex * getDuplicateVertex() {
        return duplicateVertex;
    }

    void setDuplicateVertex(Vertex * duplicateVertex) {
        this -> duplicateVertex = duplicateVertex;
    }
};



#endif //GRAPHICSPROJECT_VERTEX_H
