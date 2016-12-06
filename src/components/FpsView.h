//
// Created by gabriel on 19.11.2016.
//

#ifndef GRAPHICSPROJECT_FPSVIEW_H
#define GRAPHICSPROJECT_FPSVIEW_H


#include <src/rendering/Camera.h>

class FpsView {
private:
    PointerCamera camera;
    bool mouseLocked = false;
    Vector2f center = center;
public:
    FpsView(PointerCamera camera, bool flyMode = false){
        this -> camera = camera;
        center = Input::getMousePosition();
    }

    void input(){
        float movSpeed = 0.1f;
        float rotSpeed = 0.05f;
        float SENSITIVITY = 0.002f;
        float yaw = camera -> yaw;
        float pitch = camera -> pitch;
        Vector3f position = camera -> position;

        if(mouseLocked) {
            Vector2f deltaPos = Input::getMousePosition() - center;
            bool rotY = deltaPos.x != 0;
            bool rotX = deltaPos.y != 0;

            if(rotY)
                pitch += deltaPos.y * SENSITIVITY;

            if(rotX)
                yaw += deltaPos.x * SENSITIVITY;


            if(rotY || rotX)
                center = Input::getMousePosition();
        }

        if(Input::getKeyDown(GLFW_KEY_P)) {
            mouseLocked = !mouseLocked;
            if(mouseLocked)
                Input::setMousePos(Input::getWindowCenter());
            glfwSetInputMode(WindowManager::window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }


        if(Input::isKeyDown(GLFW_KEY_W)) {
            //position -> z -= movSpeed;
            position.x += static_cast<float>(cos(camera -> pitch) * sin(yaw) * movSpeed);
            position.z += static_cast<float>(-cos(camera -> pitch) * cos(yaw) * movSpeed);
        }
        if(Input::isKeyDown(GLFW_KEY_S)) {
            //position->z += movSpeed;
            position.x -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
            position.z -= static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
        }

        if(Input::isKeyDown(GLFW_KEY_A)) {
            //position->x -= movSpeed;
            position.z -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
            position.x -= static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
        }
        if(Input::isKeyDown(GLFW_KEY_D)) {
            //position->x += movSpeed;
            position.z += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
            position.x += static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
        }

        if(Input::isKeyDown(GLFW_KEY_LEFT_SHIFT ))
            position.y -= movSpeed;
        if(Input::isKeyDown(GLFW_KEY_SPACE))
            position.y += movSpeed;

        if(Input::isKeyDown(GLFW_KEY_Q))
            yaw -= rotSpeed;
        if(Input::isKeyDown(GLFW_KEY_E))
            yaw += rotSpeed;

        camera -> yaw = yaw;
        camera -> pitch = pitch;
        camera -> position = position;
    }
};


#endif //GRAPHICSPROJECT_FPSVIEW_H
