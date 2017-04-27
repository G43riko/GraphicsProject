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


	inline Vector3f toWorldCoords(Vector4f eyeCoords){
		Matrix4f invertedview = Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(viewMatrix)));

		Vector4f rayWorld = Matrix4f::transform(invertedview, eyeCoords);
		Vector3f mouseRay = Vector3f(rayWorld.x, rayWorld.y, rayWorld.z);
		return mouseRay.normalize();
	}

	inline Vector4f toEyeCoords(Vector4f clipCoords){
		Matrix4f invertedProjection =  Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(projectionMatrix)));
		Vector4f eyeCoords = Matrix4f::transform(invertedProjection, clipCoords);
		return Vector4f(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	inline Vector2f getNormalizedDeviceCoords(float mouseX, float mouseY){
		float x = (2.0f * mouseX) / (float)WindowManager::width - 1;
		float y = (2.0f * mouseY) / (float)WindowManager::height - 1;
		return Vector2f(x, -y);
	}

	void update(void);
	MousePicker(Camera * camera);

public:
	inline Vector3f calculateMouseRay(void){
		Vector2f mousePos = Input::getMousePosition();
		float mouseX = mousePos.x;
		float mouseY = mousePos.y;
		mouseX = (float)(WindowManager::width / 2);
		mouseY = (float)(WindowManager::height / 2);
		Vector2f normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
		Vector4f clipCoords = Vector4f(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		Vector4f eyeCoords = toEyeCoords(clipCoords);
		Vector3f worlRay = toWorldCoords(eyeCoords);
		return worlRay;
	}
	inline Vector3f getCurrentRay() {
		update();
		return currentRay;
	}
};


#endif //GRAPHICSPROJECT_MOUSEPICKER_H
