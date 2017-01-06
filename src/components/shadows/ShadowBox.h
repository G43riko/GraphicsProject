//
// Created by gabriel on 6.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWBOX_H
#define GRAPHICSPROJECT_SHADOWBOX_H


#include <src/utils/Matrix4f.h>
#include <src/rendering/Camera.h>

class ShadowBox {
private:
    static constexpr float OFFSET = 10.0f;
    static const float SHADOW_DISTANCE;
    static const Vector4f UP;
    static const Vector4f FORWARD;

    float minX, maxX;
    float minY, maxY;
    float minZ, maxZ;
    Matrix4f * lightViewMatrix;
    PointerCamera cam;
    float farHeight, farWidth, nearHeight, nearWidth;

    Vector4f * calculateFrustumVertices(Matrix4f rotation, Vector3f forwardVector, Vector3f centerNear, Vector3f centerFar) {
        Vector3f upVector = Vector3f(Matrix4f::transform(rotation, UP, nullptr));
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

    void update(void);

    Vector3f getCenter() {
        float x = (minX + maxX) / 2.0f;
        float y = (minY + maxY) / 2.0f;
        float z = (minZ + maxZ) / 2.0f;
        Vector4f cen = Vector4f(x, y, z, 1);
        Matrix4f invertedLight = Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(*lightViewMatrix)));
        return Vector3f(Matrix4f::transform(invertedLight, cen, nullptr));
    }

    Vector4f calculateLightSpaceFrustumCorner(Vector3f startPoint, Vector3f direction, float width) {
        Vector3f point = startPoint + Vector3f(direction.x * width, direction.y * width, direction.z * width);
        Vector4f point4f = Vector4f(point.x, point.y, point.z, 1.0f);
        Matrix4f::transform(*lightViewMatrix, point4f, &point4f);
        return point4f;
    }

    Matrix4f calculateCameraRotationMatrix() {
        Matrix4f rotation = Matrix4f();
        Matrix4f::rotate(static_cast<float>(TO_RADIANS(-cam -> yaw)), Vector3f(0, 1, 0), rotation, &rotation);
        Matrix4f::rotate(static_cast<float>(TO_RADIANS(-cam -> pitch)), Vector3f(1, 0, 0), rotation, &rotation);
        return rotation;
    }
    void calculateWidthsAndHeights() {
        farWidth = (float) (SHADOW_DISTANCE * tan(TO_RADIANS(cam -> FOV)));
        nearWidth = (float) (cam -> NEAR_PLANE * tan(TO_RADIANS(cam -> FOV)));
        farHeight = farWidth / getAspectRatio();
        nearHeight = nearWidth / getAspectRatio();
    }

    float getAspectRatio() {
        return WindowManager::getRation();
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
