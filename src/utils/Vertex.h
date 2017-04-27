//
// Created by gabriel on 29.9.2016.
//

#ifndef GRAPHICSPROJECT_VERTEX_H
#define GRAPHICSPROJECT_VERTEX_H

#include "Vectors.h"
#include <vector>

#define NO_INDEX -1

class Vertex;
typedef std::shared_ptr<Vertex> PointerVertex;
class Vertex {
private:
    int textureIndex = NO_INDEX;
    int normalIndex = NO_INDEX;
    PointerVertex duplicateVertex = nullptr;
    long unsigned int index;
    float length;
    std::vector<Vector3f> tangents = std::vector<Vector3f>();
    Vector3f averagedTangent = Vector3f(0, 0, 0);
public:
    Vector3f position;
    inline Vertex(long unsigned int index,Vector3f position){
        this -> index = index;
        this -> position = position;
        this -> length = position.length();
    }
    inline void show(void) const{
        printf("texture: %d, normal: %d\n", textureIndex, normalIndex);
        position.show();
    }
    inline void addTangent(Vector3f tangent){
        tangents.push_back(tangent);
    }

    inline void averageTangents(void){
        if(tangents.size() == 0){
            return;
        }
        for(Vector3f tangent : tangents){
            //averagedTangent -> add(tangent);
            averagedTangent += tangent;
        }
    }



    inline bool isSet(void) const{return textureIndex != NO_INDEX && normalIndex != NO_INDEX;}

    inline bool hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther)const{
        return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
    }


    inline float getLength(void)const{return length; }
    inline Vector3f getAverageTangent(void) const{return averagedTangent; }
    inline long unsigned int getIndex(void)const{return index; }
    inline Vector3f getPosition(void)const{return position; }
    inline int getTextureIndex(void)const{return textureIndex; }
    inline int getNormalIndex(void)const{return normalIndex; }
    inline PointerVertex getDuplicateVertex(void)const{return duplicateVertex; }

    inline void setTextureIndex(int textureIndex){this -> textureIndex = textureIndex; }
    inline void setNormalIndex(int normalIndex){this -> normalIndex = normalIndex; }
    inline void setDuplicateVertex(PointerVertex duplicateVertex){this -> duplicateVertex = duplicateVertex; }
};



#endif //GRAPHICSPROJECT_VERTEX_H
