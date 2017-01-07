//
// Created by gabriel on 7.1.2017.
//

#include "ParticleMaster.h"

void ParticleMaster::renderParticles(std::vector<Particle> particles, PointerRawModel model, PointerCamera camera) {
    if(particles.empty()){
        return;
    }
    shader -> bind();
    utils -> prepareModel(model, 1);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glm::mat4 viewMatrix = camera -> getViewMatrix();

    for(unsigned int i=0 ; i<particles.size() ; i++){
        Particle p = particles[i];
        Matrix4f mat;
        Matrix4f::setIdentity(mat);
        Matrix4f::translate(p.getPosition(), mat, &mat);
//        mat.m00 = viewMatrix[0][0];
//        mat.m01 = viewMatrix[1][0];
//        mat.m02 = viewMatrix[2][0];
//        mat.m10 = viewMatrix[0][1];
//        mat.m11 = viewMatrix[1][1];
//        mat.m12 = viewMatrix[2][1];
//        mat.m20 = viewMatrix[0][2];
//        mat.m21 = viewMatrix[1][2];
//        mat.m22 = viewMatrix[2][2];
//
//
//        mat.m00 = viewMatrix[0][0];
//        mat.m01 = viewMatrix[0][1];
//        mat.m02 = viewMatrix[0][2];
//        mat.m10 = viewMatrix[1][0];
//        mat.m11 = viewMatrix[1][1];
//        mat.m12 = viewMatrix[1][2];
//        mat.m20 = viewMatrix[2][0];
//        mat.m21 = viewMatrix[2][1];
//        mat.m22 = viewMatrix[2][2];
        Matrix4f::rotate(static_cast<float>(TO_RADIANS(p.getRotation())), Vector3f(0, 0, 1), mat, &mat);
        Matrix4f::scale(Vector3f(p.getScale()), mat, &mat);
        Matrix4f::mul(Matrix4f(viewMatrix), mat, &mat);
        shader -> updateUniform4m("modelViewMatrix", mat);
//        shader -> updateUniform4m("modelViewMatrix", viewMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());

    }

    utils -> finishRender(1);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}