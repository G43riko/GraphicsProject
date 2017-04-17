//
// Created by gabriel on 1.4.2017.
//

#include "MousePicker.h"

Vector3f MousePicker::calculateMouseRay(){
    Vector2f mousePos = Input::getMousePosition();
    float mouseX = mousePos.x;
    float mouseY = mousePos.y;
    mouseX = WindowManager::width / 2;
    mouseY = WindowManager::height / 2;
    Vector2f normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
    Vector4f clipCoords = Vector4f(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    Vector4f eyeCoords = toEyeCoords(clipCoords);
    Vector3f worlRay = toWorldCoords(eyeCoords);
    return worlRay;
}

Vector3f MousePicker::toWorldCoords(Vector4f eyeCoords){
    Matrix4f invertedview = Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(viewMatrix)));

    Vector4f rayWorld = Matrix4f::transform(invertedview, eyeCoords);
    Vector3f mouseRay = Vector3f(rayWorld.x, rayWorld.y, rayWorld.z);
    return mouseRay.normalize();
}

Vector4f MousePicker::toEyeCoords(Vector4f clipCoords){
    Matrix4f invertedProjection =  Matrix4f(glm::inverse(Matrix4f::toGlmMatrix(projectionMatrix)));
    Vector4f eyeCoords = Matrix4f::transform(invertedProjection, clipCoords);
    return Vector4f(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

Vector2f MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY){
    float x = (2.0f * mouseX) / (float)WindowManager::width - 1;
    float y = (2.0f * mouseY) / (float)WindowManager::height - 1;
    return Vector2f(x, -y);
}

void MousePicker::update(){
    PRINT("pitch: " << camera -> pitch << " yaw: " << camera -> yaw);
    viewMatrix = Maths::createViewMatrix(-camera -> pitch,      -camera -> yaw,        camera -> roll,
                                         camera -> position.x, camera -> position.y, camera -> position.z);
    currentRay = calculateMouseRay();
}
MousePicker::MousePicker(Camera * camera) {
    this -> projectionMatrix = camera -> getProjectionMatrix();
    this -> camera = camera;
    //		this.viewMatrix = Maths.MatrixToGMatrix(Maths.createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw()));

}

Vector3f MousePicker::getCurrentRay() {
    update();
    return currentRay;
}