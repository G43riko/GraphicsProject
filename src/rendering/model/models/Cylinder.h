//
// Created by gabriel on 22.5.2017.
//

#ifndef GAMEENGINE_CYLINDER_H
#define GAMEENGINE_CYLINDER_H

#include "Model.h"

class Cylinder : public Model{
    //(radiusTop, radiusBottom, height, radiusSegments, heightSegments, openEnded, thetaStart, thetaLength)
    float _radiusTop;
    float _radiusBottom;
    float _height;
    uint _radiusSemgments;
    uint _heightSegments;
    bool _openEnded;
    float _thetaStart;
    float _thetaLength;
public:
    inline Cylinder(float radiusTop,
                    float radiusBottom,
                    float height,
                    uint radiusSegments = 24,
                    uint heightSegments = 1,
                    bool openEnded = false,
                    float thetaStart = 0.0f,
                    float thetaLenght = (float)M_PI) :
            _radiusTop(radiusTop),
            _radiusBottom(radiusBottom),
            _height(height),
            _radiusSemgments(radiusSegments),
            _heightSegments(heightSegments),
            _openEnded(openEnded),
            _thetaStart(thetaStart),
            _thetaLength(thetaLenght){

        generateModel();
        setMesh();
    };

    inline std::vector<Vector3f> getCirclePoints(const Vector3f& center, const float radius) const{
        const float step = (float)(M_PI * 2) / (float)_radiusSemgments;
        std::vector<Vector3f> result;

        result.reserve(_radiusSemgments);

        float actAngle = 0;
        LOOP_U(_radiusSemgments, i){
            result.push_back(Vector3f(center.x + COSF(actAngle) * _radiusTop,
                                      center.y,
                                      center.z + SINF(actAngle) * _radiusTop));
            actAngle+=step;
        }

        return result;
    }

    inline void generateModel(void) {
        const std::vector<Vector3f> topCircle = getCirclePoints(Vector3f(0.0f, _height / 2, 0.0f), _radiusTop);
        const std::vector<Vector3f> bottomCircle = getCirclePoints(Vector3f(0.0f, -_height / 2, 0.0f), _radiusBottom);
        const float radiusSteps = 1.0f / (float)_radiusSemgments;

        /*
         * LH PH
         * LD PD
         */
        float texturesOffset = 0;
        LOOP_U_EQ(_radiusSemgments, i){
            const uint modResult = i % _radiusSemgments;
            finalPositions.push_back(topCircle[modResult].x);
            finalPositions.push_back(topCircle[modResult].y);
            finalPositions.push_back(topCircle[modResult].z);
            finalPositions.push_back(bottomCircle[modResult].x);
            finalPositions.push_back(bottomCircle[modResult].y);
            finalPositions.push_back(bottomCircle[modResult].z);

            finalTextures.push_back(0.0f);
            finalTextures.push_back(texturesOffset);
            finalTextures.push_back(1.0f);
            finalTextures.push_back(texturesOffset);

            Vector3f normal1 = topCircle[modResult].getNormal();
            finalNormals.push_back(normal1.x);
            finalNormals.push_back(normal1.y);
            finalNormals.push_back(normal1.z);

            Vector3f normal2 = bottomCircle[modResult].getNormal();
            finalNormals.push_back(normal2.x);
            finalNormals.push_back(normal2.y);
            finalNormals.push_back(normal2.z);

            if(i > 0){
                const uint ph = i << 1;
                const uint pd = ph + 1;
                const uint lh = ph - 2;
                const uint ld = ph - 1;

                indices.push_back(lh);
                indices.push_back(pd);
                indices.push_back(ld);

                indices.push_back(lh);
                indices.push_back(ph);
                indices.push_back(pd);
            }
            texturesOffset += radiusSteps;
        }
    }

};
#endif //GAMEENGINE_CYLINDER_H
