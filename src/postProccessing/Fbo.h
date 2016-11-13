//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_FBO_H
#define GRAPHICSPROJECT_FBO_H

#include <src/rendering/material/Texture2D.h>
#include "../rendering/WindowManager.h"

class Fbo {
private:
    bool multisample = false;
public:
    static int NONE, DEPTH_TEXTURE, DEPTH_RENDER_BUFFER;
    Fbo(int width, int height, int depthBufferType) {
        this -> width = width;
        this -> height = height;
        initialiseFrameBuffer(depthBufferType);
    }
    Fbo(int width, int height) {
        this -> width = width;
        this -> height = height;
        this -> multisample = true;
        initialiseFrameBuffer(DEPTH_RENDER_BUFFER);
    }

    void cleanUp() {
        glDeleteFramebuffers(1, &frameBuffer);
        glDeleteTextures(1, &colourTexture);
        glDeleteTextures(1, &depthTexture);
        glDeleteRenderbuffers(1, &depthBuffer);
        glDeleteRenderbuffers(1, &colourBuffer);
        glDeleteRenderbuffers(1, &colourBuffer2);//TODO nahradiť vectorom
    }

    void bindFrameBuffer() {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void unbindFrameBuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowManager::width, WindowManager::height);
    }

    void bindToRead() {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
    }


    void resolveToFbo(GLenum readBuffer, Fbo output){
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.frameBuffer);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(readBuffer);
        glBlitFramebuffer(0, 0, width, height, 0, 0, output.width, output.height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        unbindFrameBuffer();
    }
    void resolveToScreen(){
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(GL_COLOR_ATTACHMENT0);//toto som sem pridal aby sa vždy prepol na GL_COLOR_ATTACHMENT0 pri vykreslovaní sceny
        glDrawBuffer(GL_BACK);
        glBlitFramebuffer(0, 0, width, height,  0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        unbindFrameBuffer();
    }

    int getColourTexture() {
        return colourTexture;
    }

    int getDepthTexture() {
        return depthTexture;
    }
private :
    int width;
    int height;

    GLuint frameBuffer;
    GLuint colourTexture;
    GLuint depthTexture;

    static GLuint depthBuffer;
    static GLuint colourBuffer;
    static GLuint colourBuffer2;//TODO nahradiť vektorom

    void determineDrawBuffer(){
        std::vector<GLenum> buffer;
        buffer.push_back(GL_COLOR_ATTACHMENT0);
        if(multisample)//TODO prerobiť na pridávanie s vektora
            buffer.push_back(GL_COLOR_ATTACHMENT1);

        glDrawBuffers(buffer.size(), buffer.data());
    }

    void initialiseFrameBuffer(int type) {
        createFrameBuffer();
        if(multisample){
            createMultisampleColorAttachment(&colourBuffer, GL_COLOR_ATTACHMENT0);
            createMultisampleColorAttachment(&colourBuffer2, GL_COLOR_ATTACHMENT1);//TODO pridať načítavanie s vektora
        }
        else
            createTextureAttachment();

        if (type == DEPTH_RENDER_BUFFER) {
            createDepthBufferAttachment();
        } else if (type == DEPTH_TEXTURE) {
            createDepthTextureAttachment();
        }
        unbindFrameBuffer();
    }

    void createFrameBuffer() {
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        determineDrawBuffer();
    }

    void createMultisampleColorAttachment(GLuint * buffer, int attach){
        glGenRenderbuffers(1, buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, *buffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attach, GL_RENDERBUFFER, *buffer);
    };

    void createTextureAttachment() {
        glGenTextures(1, &colourTexture);
        glBindTexture(GL_TEXTURE_2D, colourTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_INT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colourTexture, 0);
    }

    void createDepthTextureAttachment() {
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    }

    void createDepthBufferAttachment() {
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        if(multisample)
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, width, height);
        else
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    };
};

#endif //GRAPHICSPROJECT_FBO_H
