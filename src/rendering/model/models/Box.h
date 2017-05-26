//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_BOX_H
#define GAMEENGINE_BOX_H

#include "Model.h"

class Box : public Model{
    float _width;
    float _height;
    float _depth;
    uint _widthSegments;
    uint _heightSegments;
    uint _depthSegments;


    uint numberOfVertices = 0;
    uint groupStart = 0;

    inline static void setToVector(Vector3f& vector, char type, float value){
        if(type == 'x'){
            vector.x = value;
        }
        else if(type == 'y'){
            vector.y = value;
        }
        else if(type == 'z'){
            vector.y = value;
        }
    }

    void buildPlane(char u,
                    char v,
                    char w,
                    int udir,
                    int vdir,
                    float width,
                    float height,
                    float depth,
                    uint gridX,
                    uint gridY,
                    uint materialIndex){
        float segmentWidth = width / (float)gridX;
        float segmentHeight = height / (float)gridY;

        float widthHalf = width / 2;
        float heightHalf = height / 2;
        float depthHalf = depth / 2;

        uint gridX1 = gridX + 1;
        uint gridY1 = gridY + 1;

        uint vertexCounter = 0;
        uint groupCount = 0;

//            var ix, iy;

        Vector3f vector;

        // generate vertices, normals and uvs

        LOOP_U(gridY1, iy){

            float y = (float)iy * segmentHeight - heightHalf;
            LOOP_U(gridX1, ix){
                float x = (float)ix * segmentWidth - widthHalf;

                // set values to correct vector component

                setToVector(vector, u, x * (float)udir);
                setToVector(vector, v, y * (float)vdir);
                setToVector(vector, w, depthHalf);


                // now apply vector to vertex buffer
                finalPositions.push_back(vector.x);
                finalPositions.push_back(vector.y);
                finalPositions.push_back(vector.z);

                // set values to correct vector component

                setToVector(vector, u, 0);
                setToVector(vector, v, 0);
                setToVector(vector, w, depth > 0 ? 1 : - 1);

                // now apply vector to normal buffer

                finalNormals.push_back(vector.x);
                finalNormals.push_back(vector.y);
                finalNormals.push_back(vector.z);

                // uvs

                finalTextures.push_back( (float)ix / (float)gridX );
                finalTextures.push_back( 1 - ( (float)iy / (float)gridY ) );

                // counters

                vertexCounter += 1;

            }

        }

        // indices

        // 1. you need three indices to draw a single face
        // 2. a single segment consists of two faces
        // 3. so we need to generate six (2*3) indices per segment
        LOOP_U(gridY, iy){
            LOOP_U(gridX, ix){

                uint a = numberOfVertices + ix + gridX1 * iy;
                uint b = numberOfVertices + ix + gridX1 * ( iy + 1 );
                uint c = numberOfVertices + ( ix + 1 ) + gridX1 * ( iy + 1 );
                uint d = numberOfVertices + ( ix + 1 ) + gridX1 * iy;

                // faces

                indices.push_back(a);
                indices.push_back(d);
                indices.push_back(b);

                indices.push_back(b);
                indices.push_back(d);
                indices.push_back(c);

                // increase counter

                groupCount += 6;

            }

        }

        // add a group to the geometry. this will ensure multi material support

//        scope.addGroup( groupStart, groupCount, materialIndex );

        // calculate new start value for groups

        groupStart += groupCount;

        // update total number of vertices

        numberOfVertices += vertexCounter;

    };

public:
    inline Box(float width,
               float height,
               float depth,
               uint widthSegments = 1,
               uint heightSegments = 1,
               uint depthSegments = 1):
            _width(width),
            _height(height),
            _depth(depth),
            _widthSegments(widthSegments),
            _heightSegments(heightSegments),
            _depthSegments(depthSegments){

        generateModel();
        setMesh();
    }

    inline void generateModel(void){
        numberOfVertices = 0;
        groupStart = 0;

        buildPlane('z', 'y', 'x', - 1, - 1, _depth, _height,   _width,  _depthSegments, _heightSegments, 0 ); // px
        buildPlane('z', 'y', 'x',   1, - 1, _depth, _height, - _width,  _depthSegments, _heightSegments, 1 ); // nx
        buildPlane('x', 'z', 'y',   1,   1, _width, _depth,    _height, _widthSegments, _depthSegments,  2 ); // py
        buildPlane('x', 'z', 'y',   1, - 1, _width, _depth,  - _height, _widthSegments, _depthSegments,  3 ); // ny
        buildPlane('x', 'y', 'z',   1, - 1, _width, _height,   _depth,  _widthSegments, _heightSegments, 4 ); // pz
        buildPlane('x', 'y', 'z', - 1, - 1, _width, _height, - _depth,  _widthSegments, _heightSegments, 5 ); // nz
    }
};

#endif //GAMEENGINE_BOX_H
