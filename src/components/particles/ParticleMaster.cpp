//
// Created by gabriel on 7.1.2017.
//

#include "ParticleMaster.h"
#include <glm/gtx/string_cast.hpp>

void ParticleMaster::renderParticles(std::vector<Particle> particles, PointerCamera camera) {
    if(particles.empty()){
        return;
    }
    shader -> bind();
    utils -> prepareModel(model, 1);
    glm::mat4 viewMatrix = camera -> getViewMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    for(unsigned int i=0 ; i<particles.size() ; i++){
        Particle p = particles[i];
        Matrix4f mat = Matrix4f::initTranslation(p.getPosition().x, p.getPosition().y, p.getPosition().z);
        mat.m00 = viewMatrix[0][0];
        mat.m01 = viewMatrix[0][1];
        mat.m02 = viewMatrix[0][2];
        mat.m10 = viewMatrix[1][0];
        mat.m11 = viewMatrix[1][1];
        mat.m12 = viewMatrix[1][2];
        mat.m20 = viewMatrix[2][0];
        mat.m21 = viewMatrix[2][1];
        mat.m22 = viewMatrix[2][2];

        mat = Matrix4f::initRotation(0, 0, p.getRotation()) * mat;
        Matrix4f::scale(Vector3f(p.getScale()), mat, &mat);
        mat = mat * Matrix4f(viewMatrix);
        shader -> updateUniform4m("modelViewMatrix", mat);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());

    }

    utils -> finishRender(1);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}