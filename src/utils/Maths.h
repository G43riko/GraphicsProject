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
#include <glm/gtx/transform.hpp>

class Maths {
    public:
        static glm::mat4 createTransformationMatrix(const float &, const float &, const float &,
                                                    const float &, const float &, const float &,
                                                    const float &, const float &, const float &);
        static glm::mat4 createViewMatrix(const float &, const float &, const float &, const float &, const float &);
        static glm::mat4 createTransformationMatrix(const float &, const float &, const float &, const float &);
        static glm::mat4 createTransformationMatrix(Vector2f *, Vector2f *);
        static glm::mat4 createTransformationMatrix(Transform *);
};


#endif //GRAPHICSPROJECT_MATHS_H
