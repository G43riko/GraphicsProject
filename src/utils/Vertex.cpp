//
// Created by gabriel on 29.9.2016.
//

#include "Vertex.h"

Vector3f * position;
Vertex::Vertex(long unsigned int index,Vector3f * position){
    this -> index = index;
    this -> position = position;
    this -> length = position -> getLength();
}
void Vertex::show(void){
    position -> show();
}
void Vertex::addTangent(Vector3f * tangent){
    tangents.push_back(tangent);
}

void Vertex::averageTangents(void){
    if(tangents.size() == 0){
        return;
    }
    for(Vector3f * tangent : tangents){
        averagedTangent -> add(tangent);
    }
    averagedTangent -> normalize();
}

Vector3f * Vertex::getAverageTangent(void){
    return averagedTangent;
}

long unsigned int Vertex::getIndex(void){
    return index;
}

float Vertex::getLength(void){
    return length;
}

bool Vertex::isSet(void){
    return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther){
    return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void Vertex::setTextureIndex(int textureIndex){
    this -> textureIndex = textureIndex;
}

void Vertex::setNormalIndex(int normalIndex){
    this -> normalIndex = normalIndex;
}

Vector3f * Vertex::getPosition(void){
    return position;
}

int Vertex::getTextureIndex(void){
    return textureIndex;
}

int Vertex::getNormalIndex(void){
    return normalIndex;
}

Vertex * Vertex::getDuplicateVertex(void){
    return duplicateVertex;
}

void Vertex::setDuplicateVertex(Vertex * duplicateVertex){
    this -> duplicateVertex = duplicateVertex;
}