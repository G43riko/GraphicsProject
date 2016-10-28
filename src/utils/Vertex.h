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
        Vertex(long unsigned int,Vector3f * );
        void show(void);
        void addTangent(Vector3f *);
        void averageTangents(void);
        bool isSet(void);
        bool hasSameTextureAndNormal(int, int);

        void setTextureIndex(int);
        void setNormalIndex(int);
        void setDuplicateVertex(Vertex *);

        Vector3f * getPosition(void);
        Vertex * getDuplicateVertex(void);
        Vector3f * getAverageTangent(void);
        long unsigned int getIndex(void);
        int getTextureIndex(void);
        int getNormalIndex(void);
        float getLength(void);
};



#endif //GRAPHICSPROJECT_VERTEX_H
