//
// Created by gabriel on 6.1.2017.
//

#include "ShadowBox.h"

const Vector4f ShadowBox::UP = Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4f ShadowBox::FORWARD = Vector4f(0.0f, 0.0f, -1.0f, 0.0f);
 const float ShadowBox::SHADOW_DISTANCE = 100.0f;
void ShadowBox::update(void) {
    Matrix4f rotation = calculateCameraRotationMatrix();
    Vector3f forwardVector = Vector3f(Matrix4f::transform(rotation, FORWARD, nullptr));

    Vector3f toFar = Vector3f(forwardVector) * SHADOW_DISTANCE;
    Vector3f toNear = Vector3f(forwardVector) * cam -> NEAR_PLANE;
    Vector3f centerNear = toNear + cam -> position;
    Vector3f centerFar = toFar + cam -> position;

    Vector4f * points = calculateFrustumVertices(rotation, forwardVector, centerNear,
                                                 centerFar);

    bool first = true;
    //for (Vector4f point : points) {
    for(int i=0 ; i<8 ; i++){
        Vector4f point = points[i];
        if (first) {
            minX = point.x;
            maxX = point.x;
            minY = point.y;
            maxY = point.y;
            minZ = point.z;
            maxZ = point.z;
            first = false;
            continue;
        }
        if (point.x > maxX) {
            maxX = point.x;
        } else if (point.x < minX) {
            minX = point.x;
        }
        if (point.y > maxY) {
            maxY = point.y;
        } else if (point.y < minY) {
            minY = point.y;
        }
        if (point.z > maxZ) {
            maxZ = point.z;
        } else if (point.z < minZ) {
            minZ = point.z;
        }
    }
    maxZ += OFFSET;

    delete[] points;
}