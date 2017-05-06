//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_FBO_H
#define GRAPHICSPROJECT_FBO_H

#include <src/rendering/material/Texture2D.h>
#include "src/rendering/WindowManager.h"


class Fbo {
private :
    bool multisample = false;

    unsigned int buffersCount;
    int width;
    int height;

    GLuint frameBuffer;
    GLuint colourTexture;
    GLuint depthTexture;

    GLuint depthBuffer;
    GLuint * colorBuffers;

    inline void determineDrawBuffer(void){
        std::vector<GLenum> buffer;
        for(unsigned int i=0 ; i<buffersCount ; i++)
            buffer.push_back(GL_COLOR_ATTACHMENT0 + i);
        glDrawBuffers(static_cast<int>(buffer.size()), buffer.data());
    }
    inline void createFrameBuffer(void) {
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        determineDrawBuffer();
    }

    inline void createMultisampleColorAttachment(GLuint * buffer, const GLuint attach) const{
        glGenRenderbuffers(1, buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, *buffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attach, GL_RENDERBUFFER, *buffer);
    }

    inline void createTextureAttachment(void){
        glGenTextures(1, &colourTexture);
        glBindTexture(GL_TEXTURE_2D, colourTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_INT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colourTexture, 0);
    }

    inline void createDepthTextureAttachment(void){
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    }

    inline void createDepthBufferAttachment(void){
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        if(multisample){
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, width, height);//TODO tu je namiesto 24 16
        }
        else{
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        }
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
    }
public:
    Fbo(int width, int height) : Fbo(width, height, FBO_DEPTH_RENDER_BUFFER, 2){}
    Fbo(int width, int height, int depthBufferType):Fbo(width, height, depthBufferType, 1){}
    Fbo(int width, int height, int depthBufferType, unsigned int buffersCount) {
        this -> width = width;
        this -> height = height;
        this -> buffersCount = buffersCount;
        colorBuffers = new GLuint[buffersCount];
        multisample = buffersCount > 1;
        initialiseFrameBuffer(depthBufferType);
    }


    inline void cleanUp(void) const{
        glDeleteFramebuffers(1, &frameBuffer);
        glDeleteTextures(1, &colourTexture);
        glDeleteTextures(1, &depthTexture);
        glDeleteRenderbuffers(1, &depthBuffer);

        for(unsigned int i=0 ; i<buffersCount ; i++){
            glDeleteRenderbuffers(1, &colorBuffers[i]);
        }

        delete[] colorBuffers;

//        glDeleteRenderbuffers(1, &colourBuffer);
//        glDeleteRenderbuffers(1, &colourBuffer2);//TODO nahradiť vectorom
    }

    inline void bindFrameBuffer(void) const{
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void unbindFrameBuffer() const{
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowManager::width, WindowManager::height);
    }

    inline void bindToRead(void) const{
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(GL_COLOR_ATTACHMENT0);
    }


    inline void resolveToFbo(GLenum readBuffer, Fbo output) const{
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.frameBuffer);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(readBuffer);
        glBlitFramebuffer(0, 0, width, height, 0, 0, output.width, output.height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        unbindFrameBuffer();
    }
    inline void resolveToScreen(GLenum buffer = GL_COLOR_ATTACHMENT0) const{
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
        glReadBuffer(buffer);//toto som sem pridal aby sa vždy prepol na GL_COLOR_ATTACHMENT0 pri vykreslovaní sceny
        glDrawBuffer(GL_BACK);
        glBlitFramebuffer(0, 0, width, height,  0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        unbindFrameBuffer();
    }

    inline void initialiseFrameBuffer(int type){
        createFrameBuffer();
        if(multisample){
            for(unsigned int i=0 ; i<buffersCount ; i++){
                createMultisampleColorAttachment(&colorBuffers[i], GL_COLOR_ATTACHMENT0 + i);
            }
        }
        else{
            createTextureAttachment();
        }

        if (type == FBO_DEPTH_RENDER_BUFFER){
            createDepthBufferAttachment();
        }
        else if (type == FBO_DEPTH_TEXTURE){
            createDepthTextureAttachment();
        }
        unbindFrameBuffer();
    }

    inline unsigned int getBuffersCount(void) const{ return buffersCount; }
    inline GLuint getColourTexture(void) const{return colourTexture; }
    inline GLuint getDepthTexture(void) const{return depthTexture; }
    inline GLuint getDepthBuffer(void) const{return depthBuffer; }
};

#endif //GRAPHICSPROJECT_FBO_H
