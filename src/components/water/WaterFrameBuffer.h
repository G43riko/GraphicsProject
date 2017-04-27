//
// Created by gabriel on 31.10.2016.
//

#ifndef GRAPHICSPROJECT_WATERFRAMEBUFFER_H
#define GRAPHICSPROJECT_WATERFRAMEBUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/rendering/WindowManager.h>

#define REFLECTION_WIDTH 320 * 8
#define REFLECTION_HEIGHT 180 * 8
#define REFRACTION_WIDTH 1280
#define REFRACTION_HEIGHT 720

class WaterFrameBuffer {
    private:
        GLuint reflectionFrameBuffer;
        GLuint reflectionTexture;
        GLuint reflectionDepthBuffer;

        GLuint refractionFrameBuffer;
        GLuint refractionTexture;
        GLuint refractionDepthTexture;
    public:
        inline WaterFrameBuffer(void) {//call when loading the game
            initialiseReflectionFrameBuffer();
            initialiseRefractionFrameBuffer();
        }

        inline void cleanUp(void) const{//call when closing the game
            glDeleteFramebuffers(1, &reflectionFrameBuffer);
            glDeleteTextures(1, &reflectionTexture);
            glDeleteRenderbuffers(1, &reflectionDepthBuffer);
            glDeleteFramebuffers(1, &refractionFrameBuffer);
            glDeleteTextures(1, &refractionTexture);
            glDeleteTextures(1, &refractionDepthTexture);
        }

        inline void bindReflectionFrameBuffer(void) const{//call before rendering to this FBO
            bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
            glViewport(0, 0, REFLECTION_WIDTH, REFLECTION_HEIGHT);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        inline void bindRefractionFrameBuffer(void) const{//call before rendering to this FBO
            bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
            glViewport(0, 0, REFRACTION_WIDTH, REFRACTION_HEIGHT);
            glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        inline void unbindCurrentFrameBuffer(void) const{//call to switch to default frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, WindowManager::width, WindowManager::height);
        }

        inline GLuint getReflectionTexture(void) const{//get the resulting texture
            return reflectionTexture;
        }

        inline GLuint getRefractionTexture(void) const{//get the resulting texture
            return refractionTexture;
        }

        inline GLuint getRefractionDepthTexture(void) const{//get the resulting depth texture
            return refractionDepthTexture;
        }

        inline void initialiseReflectionFrameBuffer(void) {
            createFrameBuffer(&reflectionFrameBuffer);
            createTextureAttachment(&reflectionTexture, REFLECTION_WIDTH,REFLECTION_HEIGHT);
            createDepthBufferAttachment(&reflectionDepthBuffer, REFLECTION_WIDTH,REFLECTION_HEIGHT);
            unbindCurrentFrameBuffer();
        }

        inline void initialiseRefractionFrameBuffer(void){
            createFrameBuffer(&refractionFrameBuffer);
            createTextureAttachment(&refractionTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT);
            createDepthTextureAttachment(&refractionDepthTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT);
            unbindCurrentFrameBuffer();
        }

        inline void bindFrameBuffer(GLuint frameBuffer, const int width, const int height) const{
            glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            glViewport(0, 0, width, height);
        }
    private:
        inline void createFrameBuffer(GLuint * frameBuffer) const{
            glGenFramebuffers(1, frameBuffer);
            //generate name for frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, *frameBuffer);
            //create the framebuffer
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
            //indicate that we will always render to color attachment 0
        }

        inline void createTextureAttachment(GLuint * texture, const int width, const int height) const{
            glGenTextures(1, texture);
            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *texture, 0);
        }

        inline void createDepthTextureAttachment(GLuint * texture, const int width, int const height) const{
            glGenTextures(1, texture);
            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *texture, 0);
        }

        inline void createDepthBufferAttachment(GLuint * depthBuffer, const int width, const int height) const{
            glGenRenderbuffers(1, depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, *depthBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthBuffer);
        }
};


#endif //GRAPHICSPROJECT_WATERFRAMEBUFFER_H
