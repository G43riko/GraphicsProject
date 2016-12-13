//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_CAMERA_H
#define GRAPHICSPROJECT_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/Input.h"
#include "../rendering/WindowManager.h"
#include <sys/time.h>
#include "../utils/Vectors.h"
#include <math.h>

class Camera {
    private:
        glm::mat4 projectionMatrix;
        bool VERTICAL = true;
        const float FOV = 70.0f;
        const float NEAR_PLANE = 0.1f;
        const float FAR_PLANE = 1000.0f;
    public:
        Vector3f position = Vector3f(0, 0, 0);
        float pitch = 0;
        float yaw = 0;
        float roll = 0;
        Camera(void);
        glm::mat4 getProjectionMatrix(void);
        glm::mat4 getViewMatrix(void);
        void show(){
            printf("pitch: %f, yaw: %f, roll: %f\n", pitch, yaw, roll);
        }
};

typedef std::shared_ptr<Camera> PointerCamera;

#include "../utils/Maths.h"
#endif //GRAPHICSPROJECT_CAMERA_H
