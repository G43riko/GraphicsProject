//
// Created by gabriel on 1.4.2017.
//

#ifndef GRAPHICSPROJECT_MOUSEPICKER_H
#define GRAPHICSPROJECT_MOUSEPICKER_H


#include "Vectors.h"
#include "Matrix4f.h"
#include "../rendering/Camera.h"
class Camera;

class MousePicker {
private:
    Vector3f currentRay;
	Matrix4f projectionMatrix;
	Matrix4f viewMatrix;
	Camera * camera;

    Vector3f calculateMouseRay(void);
    Vector3f toWorldCoords(Vector4f eyeCoords);
    Vector4f toEyeCoords(Vector4f clipCoords);
    Vector2f getNormalizedDeviceCoords(float mouseX, float mouseY);
    void update(void);
public:
    MousePicker(Camera * camera);
    Vector3f getCurrentRay(void);
};


#endif //GRAPHICSPROJECT_MOUSEPICKER_H
