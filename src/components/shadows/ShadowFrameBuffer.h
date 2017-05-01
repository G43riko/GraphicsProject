//
// Created by gabriel on 8.1.2017.
//

#ifndef GRAPHICSPROJECT_SHADOWFRAMEBUFFER_H
#define GRAPHICSPROJECT_SHADOWFRAMEBUFFER_H


#include <src/rendering/WindowManager.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShadowFrameBuffer {
public:
    ShadowFrameBuffer(int width, int height) : WIDTH(width), HEIGHT(height){
        initialiseFrameBuffer();
    }

    void cleanUp() {
        glDeleteFramebuffers(1, &fbo);
        glDeleteTextures(1, &shadowMap);
    }

    void bindFrameBuffer(void) {
        bindFrameBuffer(fbo, WIDTH, HEIGHT);
    }

    void unbindFrameBuffer(void) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowManager::width, WindowManager::height);
    }

    inline GLuint getShadowMap(void) const{
        return shadowMap;
    }
private:
    const int WIDTH;
    const int HEIGHT;
    GLuint fbo;
    GLuint shadowMap;



    void initialiseFrameBuffer() {
        createFrameBuffer();
        createDepthBufferAttachment(WIDTH, HEIGHT);
        unbindFrameBuffer();
    }

    void bindFrameBuffer(int frameBuffer, int width, int height) {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }

    void createFrameBuffer() {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
    }

    void createDepthBufferAttachment(int width, int height) {
        glGenTextures(1, &shadowMap);
        glBindTexture(GL_TEXTURE_2D, shadowMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);
    }
};


#endif //GRAPHICSPROJECT_SHADOWFRAMEBUFFER_H
