//
// Created by gabriel on 7.1.2017.
//

#include "ParticleMaster.h"
#include <glm/gtx/string_cast.hpp>
void ParticleMaster::renderParticles(ParticlesList particles, PointerCamera camera) {
    if(particles.empty()){
        return;
    }
    shader -> bind();
    RenderUtil::prepareModel(model, 1);
    Matrix4f GViewMatrix = Matrix4f(camera -> getViewMatrix());
    Matrix4f mat;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDepthMask(GL_FALSE);

    //rotation
    Matrix4f rx, ry, rz;
    rx.m11 = rx.m22 = COSF(0);
    rx.m21 = SINF(0);
    rx.m12 = -rx.m21;

    ry.m00 = ry.m22 = COSF(0);
    ry.m20 = SINF(0);
    ry.m02 = -ry.m20;
    Matrix4f defaultRotation = Matrix4f::mul(ry, rx);

    for (auto it = particles.begin(); it != particles.end(); ++it){//pre všetky texture
        if(it -> second.size()){
            it->first->texture->bind(GL_TEXTURE0);
            for(unsigned long i=0, j = it->second.size(); i<j ; i++){
                Particle particle = it->second[i];

                Matrix4f::setIdentity(mat);
                //initTranslation
                mat.m03 = particle.getPosition().x;
                mat.m13 = particle.getPosition().y;
                mat.m23 = particle.getPosition().z;
                //resetRotation
                mat.m00 = GViewMatrix.m00;
                mat.m01 = GViewMatrix.m10;
                mat.m02 = GViewMatrix.m20;
                mat.m10 = GViewMatrix.m01;
                mat.m11 = GViewMatrix.m11;
                mat.m12 = GViewMatrix.m21;
                mat.m20 = GViewMatrix.m02;
                mat.m21 = GViewMatrix.m12;
                mat.m22 = GViewMatrix.m22;
                //setRotation
                float rotation = TO_RADIANS(particle.getRotation());

                Matrix4f::setIdentity(rz);
                rz.m00 = rz.m11 = COSF(rotation);
                rz.m10 = SINF(rotation);
                rz.m01 = -rz.m10;


                mat = Matrix4f::mul(rz, defaultRotation) * mat;
                float scale = particle.getScale();
                Matrix4f::scale(Vector3f(scale, scale, scale), mat, &mat);
                shader -> updateUniform4m(UNIFORM_MODEL_VIEW_MATRIX, mat * GViewMatrix);

                shader -> updateUniform4f("textOffsets", particle.getTextureOffsets());
//                shader -> updateUniform2f("textOffset1", particle.getTextureOffset1());
//                shader -> updateUniform2f("textOffset2", particle.getTextureOffset2());
//                shader -> updateUniform2f("textCoordInfo", particle.getTextureInfo());
                shader -> updateUniformf("numberOfRows", particle.getTextureInfo().x);
                shader -> updateUniformf("blendFactor", particle.getTextureInfo().y);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
            }
//            auto itPart = it->second.begin();
//            while(itPart != it->second.end()){ //prejde všetky častice
//
//                Matrix4f mat = Matrix4f::initTranslation(itPart ->getPosition().x, itPart ->getPosition().y, itPart ->getPosition().z);
//                mat.m00 = viewMatrix[0][0];
//                mat.m01 = viewMatrix[0][1];
//                mat.m02 = viewMatrix[0][2];
//                mat.m10 = viewMatrix[1][0];
//                mat.m11 = viewMatrix[1][1];
//                mat.m12 = viewMatrix[1][2];
//                mat.m20 = viewMatrix[2][0];
//                mat.m21 = viewMatrix[2][1];
//                mat.m22 = viewMatrix[2][2];
//
//                mat = Matrix4f::initRotation(0, 0, itPart ->getRotation()) * mat;
//                float scale = itPart ->getScale();
//                Matrix4f::scale(Vector3f(scale, scale, scale), mat, &mat);
//                mat = mat * Matrix4f(viewMatrix);
//                shader -> updateUniform4m("modelViewMatrix", mat);
//
//                shader -> updateUniform2f("textOffset1", itPart -> getTextureOffset1());
//                shader -> updateUniform2f("textOffset2", itPart -> getTextureOffset2());
//                shader -> updateUniform2f("textCoordInfo", itPart -> getTextureInfo());
//                glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
//                itPart++;
//            }
        }
    }

    RenderUtil::finishRender(1);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}
void ParticleMaster::renderParticles(std::vector<Particle> particles, PointerCamera camera) {
    if(particles.empty()){
        return;
    }
    shader -> bind();
    RenderUtil::prepareModel(model, 1);
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
        float scale = p.getScale();
        Matrix4f::scale(Vector3f(scale, scale, scale), mat, &mat);
        mat = mat * Matrix4f(viewMatrix);
        shader -> updateUniform4m("modelViewMatrix", mat);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());

    }

    RenderUtil::finishRender(1);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}