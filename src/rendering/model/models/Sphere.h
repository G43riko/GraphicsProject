//
// Created by gabriel on 23.5.2017.
//

#ifndef GAMEENGINE_SPHERE_H
#define GAMEENGINE_SPHERE_H

#include "Model.h"

class Sphere : public Model{
    float _radius;
    uint _widthSegments;
    uint _heightSegments;
    float _phiStart;
    float _phiLength;
    float _thetaStart;
    float _thetaLength;
public:
    Sphere(const float radius = 3,
           const uint widthSegments = 8,
           const uint heightSegments = 6,
           const float phiStart = 0,
           const float phiLength = (float)M_PI * 2,
           const float thetaStart = 0,
           const float thetaLength = (float)M_PI) :
            _radius(radius),
            _widthSegments(GMAX(3, widthSegments)),
            _heightSegments(GMAX(2, heightSegments)),
            _phiStart(phiStart),
            _phiLength(phiLength),
            _thetaStart(thetaStart),
            _thetaLength(thetaLength){

        generateModel();
        setMesh();
    }

    inline void generateModel(void){
        const float thetaEnd = _thetaStart + _thetaLength;
        uint index = 0;

        //uint grid[_heightSegments + 1][_widthSegments + 1];
        uint ** grid = new uint *[_heightSegments + 1];

        LOOP_U_EQ(_heightSegments, iy){
            grid[iy] =  new uint [_widthSegments + 1];
            float v = (float)iy / (float)_heightSegments;

            LOOP_U_EQ(_widthSegments, ix){
                float u = (float)ix / (float)_widthSegments;

                Vector3f vertex(_radius * COSF(_phiStart + u * _phiLength) * SINF(_thetaStart + v * _thetaLength),
                                _radius * COSF(_thetaStart + v * _thetaLength),
                                _radius * SINF(_phiStart + u * _phiLength) * SINF(_thetaStart + v * _thetaLength));

                finalPositions.push_back(vertex.x);
                finalPositions.push_back(vertex.y);
                finalPositions.push_back(vertex.z);

                vertex.normalize();
                finalNormals.push_back(vertex.x);
                finalNormals.push_back(vertex.y);
                finalNormals.push_back(vertex.z);

                finalTextures.push_back(u);
                finalTextures.push_back(1.0f - v);

                grid[iy][ix] = index++;
            }
        }
        LOOP_U(_heightSegments, iy) {
            LOOP_U(_widthSegments, ix) {
                uint a = grid[iy][ix + 1];
                uint b = grid[iy][ix];
                uint c = grid[iy + 1][ix];
                uint d = grid[iy + 1][ix + 1];

                if(iy != 0 || _thetaStart > 0){
                    indices.push_back(a);
                    indices.push_back(d);
                    indices.push_back(b);
                }
                if(iy != _heightSegments - 1 || thetaEnd < M_PI_2){
                    indices.push_back(b);
                    indices.push_back(d);
                    indices.push_back(c);
                }
            }
            delete[] grid[iy];
        }
        delete[] grid;
    }
};

#endif //GAMEENGINE_SPHERE_H
