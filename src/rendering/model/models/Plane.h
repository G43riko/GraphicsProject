//
// Created by gabriel on 26.5.2017.
//

#ifndef GAMEENGINE_PLANE_H
#define GAMEENGINE_PLANE_H

#include "Model.h"

class Plane : public Model{
    float _width;
    float _height;
    uint _widthSegments;
    uint _heightSegments;
public:
    Plane(const float width, const float height, const uint widthSegments = 1, const uint heightSegments = 1) :
            _width(width),
            _height(height),
            _widthSegments(widthSegments),
            _heightSegments(heightSegments){

        generateModel();
        setMesh();
    };

    inline void generateModel(void){
        // generate vertices, normals and uvs

        const float width_half = _width / 2;
        const float height_half = _height / 2;

        const uint gridX1 = _widthSegments + 1;
        const uint gridY1 = _heightSegments + 1;

        const float segment_width = _width / _widthSegments;
        const float segment_height = _height / _heightSegments;

        LOOP_U(gridY1, iy){
            const float y = iy * segment_height - height_half;
            LOOP_U(gridX1, ix){
                const float x = ix * segment_width - width_half;
                finalPositions.push_back(x);
                finalPositions.push_back(-y);
                finalPositions.push_back(0);

                finalNormals.push_back(0);
                finalNormals.push_back(0);
                finalNormals.push_back(1);

                finalTextures.push_back(ix / _widthSegments);
                finalTextures.push_back(1 - iy / _heightSegments);
            }
        }
        // indices

        LOOP_U(_widthSegments, iy){
            LOOP_U(_heightSegments, ix){
                const uint a = ix + gridX1 * iy;
                const uint b = ix + gridX1 * ( iy + 1 );
                const uint c = ( ix + 1 ) + gridX1 * ( iy + 1 );
                const uint d = ( ix + 1 ) + gridX1 * iy;

                // faces

                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(d);

                indices.push_back(b);
                indices.push_back(c);
                indices.push_back(d);
            }
        }
    };
};

#endif //GAMEENGINE_PLANE_H
