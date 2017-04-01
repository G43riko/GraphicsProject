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
#include <src/utils/Transform.h>
#include <src/utils/MousePicker.h>
class MousePicker;
class Camera {
    private:
    glm::mat4 projectionMatrix;
        Transform transform     = Transform();
        bool VERTICAL           = true;
        MousePicker * picker    = nullptr;
        Vector3f forward;
    public:
        Vector3f getForward(void);
        void updateForward(){
            forward.x = (float)(sin((-yaw + 180)) * cos(-pitch));
            forward.y = (float)sin((-pitch + 180));
            forward.z = (float)(cos((-yaw)) * cos(-pitch));
            forward.normalize();
        }
        float FOV           = DEFAULT_CAMERA_FOV;
        float FAR_PLANE     = DEFAULT_CAMERA_FAR_PLANE;
        float NEAR_PLANE    = DEFAULT_CAMERA_NEAR_PLANE;
        Vector3f position   = Vector3f(DEFAULT_CAMERA_POSITION);
        float pitch         = 0;
        float roll          = 0;
        float yaw           = 0;

        Camera(void);
        glm::mat4 getProjectionMatrix(void);
        glm::mat4 getViewMatrix(void);
        void cleanUp(void);
        void show(){
            printf("pitch: %f, yaw: %f, roll: %f\n", pitch, yaw, roll);
        }
};

typedef std::shared_ptr<Camera> PointerCamera;

#include "../utils/Maths.h"
#endif //GRAPHICSPROJECT_CAMERA_H
