//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATHS_H
#define GRAPHICSPROJECT_MATHS_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Transform.h"
#include <glm/gtx/transform.hpp>


#define MATH_PI 3.1415926535897932384626433832795
#define ToRadians(x) (float)((x) * MATH_PI / 180.0f)
#define ToDegrees(x) (float)((x) * 180.0f / MATH_PI)
#ifndef CLAMP
#define CLAMP(a, b, c) (a < b ? b : a > c ? c : a);
#endif

template<typename T>
inline T linearInterpolation(const T &a, const T &b, const float &val){
    return a * val + (1 - val) * b;
}

class Maths {
public:
    static glm::mat4 createTransformationMatrix(Vector2f pos, Vector2f scale);
    static glm::mat4 createTransformationMatrix(const float &posX,   const float &posY,
                                                const float &scaleX, const float &scaleY);

    static glm::mat4 createTransformationMatrix(const float &posX,   const float &posY,   const float &posZ,
                                                const float &rotX,   const float &rotY,   const float &rotZ,
                                                const float &scaleX, const float &scaleY, const float &scaleZ);

    static glm::mat4 createViewMatrix(const float &pitch, const float &yaw, const float &roll,
                                      const float &x,     const float &y,   const float &z);



        //static glm::mat4 createTransformationMatrix(Transform *);
};


#endif //GRAPHICSPROJECT_MATHS_H
