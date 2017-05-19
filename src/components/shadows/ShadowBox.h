//
// Created by gabriel on 6.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWBOX_H
#define GRAPHICSPROJECT_SHADOWBOX_H


#include <src/utils/math/objects/Matrix4f.h>
#include <src/rendering/Camera.h>

class ShadowBox {
private:

    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
    Matrix4f * lightViewMatrix;
    PointerCamera cam;
    float farHeight, farWidth, nearHeight, nearWidth;

    Vector4f * calculateFrustumVertices(Matrix4f rotation, Vector3f forwardVector, Vector3f centerNear, Vector3f centerFar) {
        Vector3f upVector = Vector3f(Matrix4f::transform(rotation, DIR_UP, nullptr).getXYZ());
        Vector3f rightVector = forwardVector.getCross(upVector);
        Vector3f downVector = Vector3f(-upVector.x, -upVector.y, -upVector.z);
        Vector3f leftVector = Vector3f(-rightVector.x, -rightVector.y, -rightVector.z);
        Vector3f farTop = centerFar + Vector3f(upVector.x * farHeight, upVector.y * farHeight, upVector.z * farHeight);
        Vector3f farBottom = centerFar + Vector3f(downVector.x * farHeight, downVector.y * farHeight, downVector.z * farHeight);
        Vector3f nearTop = centerNear + Vector3f(upVector.x * nearHeight, upVector.y * nearHeight, upVector.z * nearHeight);
        Vector3f nearBottom = centerNear + Vector3f(downVector.x * nearHeight, downVector.y * nearHeight, downVector.z * nearHeight);
        Vector4f *points =  new Vector4f[8];
        points[0] = calculateLightSpaceFrustumCorner(farTop, rightVector, farWidth);
        points[1] = calculateLightSpaceFrustumCorner(farTop, leftVector, farWidth);
        points[2] = calculateLightSpaceFrustumCorner(farBottom, rightVector, farWidth);
        points[3] = calculateLightSpaceFrustumCorner(farBottom, leftVector, farWidth);
        points[4] = calculateLightSpaceFrustumCorner(nearTop, rightVector, nearWidth);
        points[5] = calculateLightSpaceFrustumCorner(nearTop, leftVector, nearWidth);
        points[6] = calculateLightSpaceFrustumCorner(nearBottom, rightVector, nearWidth);
        points[7] = calculateLightSpaceFrustumCorner(nearBottom, leftVector, nearWidth);
        return points;
    }
public:
    ShadowBox(Matrix4f * lightViewMatrix, PointerCamera camera) {
        this -> lightViewMatrix = lightViewMatrix;
        this -> cam = camera;
        calculateWidthsAndHeights();
    }

    void update(void){
        Matrix4f rotation = calculateCameraRotationMatrix();
        Vector3f forwardVector = Matrix4f::transform(rotation, DIR_FORWARD).getXYZ();
        Vector3f toFar = forwardVector * SHADOW_DISTANCE;
        Vector3f toNear = forwardVector * cam -> NEAR_PLANE;
        Vector3f centerNear = toNear + cam -> getPosition();
        Vector3f centerFar = toFar + cam -> getPosition();
        Vector4f* points = calculateFrustumVertices(rotation, forwardVector, centerNear,
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
        maxZ += SHADOW_OFFSET;

    };

    Vector3f getCenter() {
        float x = (minX + maxX) / 2.0f;
        float y = (minY + maxY) / 2.0f;
        float z = (minZ + maxZ) / 2.0f;
        Matrix4f invertedLight = Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(*lightViewMatrix)));
//        Vector4f cen = Vector4f(x, y, z, 1);
//        Matrix4f invertedLight = Matrix4f();
//        Matrix4f.invert(lightViewMatrix, invertedLight);
        return Vector3f(Matrix4f::transform(invertedLight, Vector4f(x, y, z, 1)).getXYZ());
    }

    Vector4f calculateLightSpaceFrustumCorner(Vector3f startPoint, Vector3f direction, float width) {
        Vector3f point = startPoint + Vector3f(direction.x * width, direction.y * width, direction.z * width);
        Vector4f point4f = Vector4f(point.x, point.y, point.z, 1.0f);
        return Matrix4f::transform(*lightViewMatrix, point4f);;
    }

    Matrix4f calculateCameraRotationMatrix() {
        //return Matrix4f::initRotation((float)(TO_RADIANS(-cam -> pitch)), (float)(TO_RADIANS(-cam -> yaw)), 0);
        return Matrix4f::initRotation((float)(-cam -> pitch), (float)(-cam -> yaw), 0);

        /*
        Matrix4f rotation = Matrix4f();
        Matrix4f::rotate(static_cast<float>(TO_RADIANS(-cam -> yaw)), Vector3f(0, 1, 0), rotation, &rotation);
        Matrix4f::rotate(static_cast<float>(TO_RADIANS(-cam -> pitch)), Vector3f(1, 0, 0), rotation, &rotation);
        return rotation;
         */
    }

    void calculateWidthsAndHeights() {
        farWidth = (float) (SHADOW_DISTANCE * tan(TO_RADIANS(cam -> FOV)));
        nearWidth = (float) (cam -> NEAR_PLANE
                             * tan(TO_RADIANS(cam -> FOV)));
        farHeight = farWidth / WindowManager::getRation();
        nearHeight = nearWidth / WindowManager::getRation();
    }


    float getWidth() {
        return maxX - minX;
    }
    float getHeight() {
        return maxY - minY;
    }
    float getLength() {
        return maxZ - minZ;
    }
};


#endif //GRAPHICSPROJECT_SHADOWBOX_H
