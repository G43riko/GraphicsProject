//
// Created by gabriel on 25.9.2016.
//

#include "Camera.h"

Vector3f * Camera::UP = new Vector3f(0, 1, 0);

Camera::Camera(void) : lastMousePos(Input::mousePos -> x, Input::mousePos -> y){
    projectionMatrix = glm::perspectiveFov<float>(FOV, static_cast<float>(WindowManager::width),
                                                  static_cast<float>(WindowManager::height), NEAR_PLANE, FAR_PLANE);
}
glm::mat4 Camera::getProjectionMatrix(void){
    return projectionMatrix;
}

float toRadians(float val){
    return val * (M_PI / 180);
}

void Camera::updateForward(void){
    forward -> z = cos((360 - yaw)) * cos((pitch));
    forward -> x = sin((360 - yaw)) * cos((pitch));
    forward -> y = sin((pitch));
    forward -> normalize();
    forward -> show();
};

void Camera::input(void){
    float movSpeed = 0.1f;
    float rotSpeed = 0.05f;
    float SENSITIVITY = 0.0002f;

    if(mouseLocked) {
        Vector2f * center = Input::getWindowCenter();
        Vector2f *deltaPos = new Vector2f(Input::mousePos -> x - center -> x, Input::mousePos -> y - center -> y);
        std::cout << "pos: " <<Input::mousePos -> x << " x " << Input::mousePos -> y;
        std::cout << ", cent: " << Input::getWindowCenter() -> x << " x " << Input::getWindowCenter() -> y << std::endl;
        //std::cout << "center: " <<center -> x << " x " << center -> y << std::endl;
        bool rotY = deltaPos -> x != 0;
        bool rotX = deltaPos -> y != 0;

        if (rotY) {
            yaw += (deltaPos -> x * SENSITIVITY);
        }
        if (rotX) {
            pitch += (deltaPos -> y * SENSITIVITY);
        }


        //lastMousePos.x = Input::mousePos.x;
        //lstMousePos.y = Input::mousePos.y;
        if (rotY || rotX) {
            Input::setMousePos(Input::getWindowCenter());
        }
    }


    if(Input::getKeyDown(Input::KEY_P)) {
        mouseLocked = !mouseLocked;
        if(mouseLocked)
            Input::setMousePos(Input::getWindowCenter());
        //glfwSetInputMode(WindowManager::window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
    }

    if(Input::isKeyDown(Input::KEY_W)) {
        //position -> z -= movSpeed;
        position -> x += cos(pitch) * sin(yaw) * movSpeed;
        position -> z += -cos(pitch) * cos(yaw) * movSpeed;
    }
    if(Input::isKeyDown(Input::KEY_S)) {
        //position->z += movSpeed;
        position -> x -= cos(pitch) * sin(yaw) * movSpeed;
        position -> z -= -cos(pitch) * cos(yaw) * movSpeed;
    }


    if(Input::isKeyDown(Input::KEY_A)) {
        //position->x -= movSpeed;
        position -> z -= cos(pitch) * sin(yaw) * movSpeed;
        position -> x -= cos(pitch) * cos(yaw) * movSpeed;
    }
    if(Input::isKeyDown(Input::KEY_D)) {
        //position->x += movSpeed;
        position -> z += cos(pitch) * sin(yaw) * movSpeed;
        position -> x += cos(pitch) * cos(yaw) * movSpeed;
    }

    if(Input::isKeyDown(Input::KEY_LSHIFT))
        position -> y -= movSpeed;
    if(Input::isKeyDown(Input::KEY_SPACE))
        position -> y += movSpeed;

    if(Input::isKeyDown(Input::KEY_Q))
        yaw -= rotSpeed;
    if(Input::isKeyDown(Input::KEY_E))
        yaw += rotSpeed;

    //updateForward();
}

Vector3f * Camera::getForwardVector(void){
    if(VERTICAL)
        return forward -> getMul(-1) -> normalize();

    return UP -> getCross(forward) -> cross(UP) -> mul(-1) -> normalize();
}

Vector3f * Camera::getRightVector(void){
    return UP -> getCross(forward) -> normalize();
}

Vector3f * Camera::getUpVector(void){
    return UP -> getNormal();
}

glm::mat4 Camera::getViewMatrix(void){
    return Maths::createViewMatrix(this);
}