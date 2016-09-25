//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATHS_H
#define GRAPHICSPROJECT_MATHS_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "../rendering/model/Transform.h"
#include "../rendering/Camera.h"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>


class Maths {
    public:
        static glm::mat4 createTransformationMatrix(Transform *);
        static glm::mat4 createViewMatrix(Camera *);
};


#endif //GRAPHICSPROJECT_MATHS_H
