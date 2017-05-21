//
// Created by gabriel on 1.4.2017.
//

#ifndef GRAPHICSPROJECT_MOUSEPICKER_H
#define GRAPHICSPROJECT_MOUSEPICKER_H


#include "src/utils/math/objects/Vectors.h"
#include "src/utils/math/objects/Matrix4f.h"
#include "../utils/Input.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
class BasicCamera;

class MousePicker {
private:
    Vector3f currentRay;
	Matrix4f projectionMatrix;
	Matrix4f viewMatrix;
	BasicCamera * camera;


	inline Vector3f toWorldCoords(const Vector4f& eyeCoords){
		const Matrix4f invertedview = Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(viewMatrix)));

		const Vector4f rayWorld = Matrix4f::transform(invertedview, eyeCoords);
		return Vector3f(rayWorld.x, rayWorld.y, rayWorld.z).normalize();
	}

	inline Vector4f toEyeCoords(const Vector4f& clipCoords){
		const Matrix4f invertedProjection =  Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(projectionMatrix)));
		const Vector4f eyeCoords = Matrix4f::transform(invertedProjection, clipCoords);
		return Vector4f(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	inline Vector2f getNormalizedDeviceCoords(float mouseX, float mouseY){
		const float x = (2.0f * mouseX) / (float)WindowManager::width - 1;
		const float y = (2.0f * mouseY) / (float)WindowManager::height - 1;
		return Vector2f(x, -y);
	}

	void update(void);

	inline Vector3f calculateMouseRay(void){
		Vector2f mousePos;// = Input::getMousePosition();
		float mouseX = mousePos.x;
		float mouseY = mousePos.y;
		mouseX = (float)(WindowManager::width / 2);
		mouseY = (float)(WindowManager::height / 2);
		const Vector2f normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
		const Vector4f clipCoords = Vector4f(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		const Vector4f eyeCoords = toEyeCoords(clipCoords);
		return toWorldCoords(eyeCoords);
	}
public:
	MousePicker(BasicCamera * camera);
	inline const Vector3f& getCurrentRay(void){
		update();
		return currentRay;
	}
};


#endif //GRAPHICSPROJECT_MOUSEPICKER_H
