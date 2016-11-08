//
// Created by gabriel on 25.9.2016.
//

#include "Camera.h"
#include <sys/time.h>

Vector3f Camera::UP(0, 1, 0);

Camera::Camera(void) : lastMousePos(Input::getMousePosition()){
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
    forward.x = static_cast<float>(xzLen * cos(yaw));
    forward.y = static_cast<float>(sin(pitch));
    forward.z = static_cast<float>(xzLen * sin(-yaw));
    /*
    forward -> z = static_cast<float>(cos((360 - yaw)) * cos((pitch)));
    forward -> x = static_cast<float>(sin((360 - yaw)) * cos((pitch)));
    forward -> y = static_cast<float>(sin((pitch)));
    */
    forward.normalize();
    forward.show();
}

bool isNotZero(float val){
    return val > 0 || val < 0;
}

void Camera::input(void){
    float movSpeed = 0.1f;
    float rotSpeed = 0.05f;
    float SENSITIVITY = 0.02f;

    timeval now;
    gettimeofday(&now, 0);
    if(setTime){
        //std::cout << now.tv_sec - tv.tv_sec << " " << now.tv_usec - tv.tv_usec << std::endl;
    }
    setTime = true;
    tv = now;

    if(mouseLocked) {
        Vector2f center = Input::getWindowCenter();
        Vector2f deltaPos = Input::getMousePosition() - center;
        bool rotY = deltaPos.x != 0;
        bool rotX = deltaPos.y != 0;

        if(rotY) {
            pitch += deltaPos.y * SENSITIVITY;
        }
        if(rotX) {
            yaw += (deltaPos.x * SENSITIVITY);
        }

        if(rotY || rotX) {
            Input::setMousePos(center);
        }
    }



    if(Input::getKeyDown(Input::KEY_P)) {
        mouseLocked = !mouseLocked;
        if(mouseLocked)
            Input::setMousePos(Input::getWindowCenter());
        glfwSetInputMode(WindowManager::window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
    }


    if(Input::isKeyDown(Input::KEY_W)) {
        //position -> z -= movSpeed;
        position.x += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position.z += static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(Input::KEY_S)) {
        //position->z += movSpeed;
        position.x -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position.z -= static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }


    if(Input::isKeyDown(Input::KEY_A)) {
        //position->x -= movSpeed;
        position.z -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position.x -= static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(Input::KEY_D)) {
        //position->x += movSpeed;
        position.z += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position.x += static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
    }

    if(Input::isKeyDown(Input::KEY_LSHIFT))
        position.y -= movSpeed;
    if(Input::isKeyDown(Input::KEY_SPACE))
        position.y += movSpeed;

    if(Input::isKeyDown(Input::KEY_Q))
        yaw -= rotSpeed;
    if(Input::isKeyDown(Input::KEY_E))
        yaw += rotSpeed;

    //updateForward();
}
/*
PointerVector3f Camera::getForwardVector(void){
    if(VERTICAL)
        return PointerVector3f(forward -> getMul(-1) -> normalize());

    //return PointerVector3f(UP.getCross(forward.get()) -> cross(&UP) -> mul(-1) -> normalize());
    return Vector
}

PointerVector3f Camera::getRightVector(void){
    return PointerVector3f(UP.getCross(forward.get()) -> normalize());
}

PointerVector3f Camera::getUpVector(void){
    return PointerVector3f(UP.getNormal());
}
*/

glm::mat4 Camera::getViewMatrix(void){
    return Maths::createViewMatrix(pitch, yaw, position.x, position.y, position.z);
}