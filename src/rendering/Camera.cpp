//
// Created by gabriel on 25.9.2016.
//

#include "Camera.h"

Vector3f Camera::UP(0, 1, 0);

Camera::Camera(void) : lastMousePos(Input::mousePos -> x, Input::mousePos -> y){
    projectionMatrix = glm::perspectiveFov<float>(FOV,
                                                  static_cast<float>(WindowManager::width),
                                                  static_cast<float>(WindowManager::height),
                                                  NEAR_PLANE,
                                                  FAR_PLANE);
}
glm::mat4 Camera::getProjectionMatrix(void){
    return projectionMatrix;
}

float toRadians(float val){
    return static_cast<float>(val * (M_PI / 180));
}

void Camera::updateForward(void){
    double xzLen = cos(pitch);
    forward -> x = static_cast<float>(xzLen * cos(yaw));
    forward -> y = static_cast<float>(sin(pitch));
    forward -> z = static_cast<float>(xzLen * sin(-yaw));
    /*
    forward -> z = static_cast<float>(cos((360 - yaw)) * cos((pitch)));
    forward -> x = static_cast<float>(sin((360 - yaw)) * cos((pitch)));
    forward -> y = static_cast<float>(sin((pitch)));
    */
    forward -> normalize();
    forward -> show();
}

bool isNotZoer(float val){
    return val > 0 || val < 0;
}

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
        bool rotY = isNotZoer(deltaPos -> x);
        bool rotX = isNotZoer(deltaPos -> y);

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
        position -> x += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> z += static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(Input::KEY_S)) {
        //position->z += movSpeed;
        position -> x -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> z -= static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }


    if(Input::isKeyDown(Input::KEY_A)) {
        //position->x -= movSpeed;
        position -> z -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> x -= static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(Input::KEY_D)) {
        //position->x += movSpeed;
        position -> z += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> x += static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
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

PointerVector3f Camera::getForwardVector(void){
    if(VERTICAL)
        return PointerVector3f(forward -> getMul(-1) -> normalize());

    return PointerVector3f(UP.getCross(forward.get()) -> cross(&UP) -> mul(-1) -> normalize());
}

PointerVector3f Camera::getRightVector(void){
    return PointerVector3f(UP.getCross(forward.get()) -> normalize());
}

PointerVector3f Camera::getUpVector(void){
    return PointerVector3f(UP.getNormal());
}

glm::mat4 Camera::getViewMatrix(void){
    return Maths::createViewMatrix(pitch, yaw, position -> x, position -> y, position -> z);
}