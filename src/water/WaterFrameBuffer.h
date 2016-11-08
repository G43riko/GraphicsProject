//
// Created by gabriel on 31.10.2016.
//

#ifndef GRAPHICSPROJECT_WATERFRAMEBUFFER_H
#define GRAPHICSPROJECT_WATERFRAMEBUFFER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WaterFrameBuffer {
    protected:
        const static int REFLECTION_WIDTH = 320;
        const static int REFRACTION_WIDTH = 1280;
    private:
        const static int REFLECTION_HEIGHT = 180;

        const static int REFRACTION_HEIGHT = 720;

        GLuint reflectionFrameBuffer;
        GLuint reflectionTexture;
        GLuint reflectionDepthBuffer;

        GLuint refractionFrameBuffer;
        GLuint refractionTexture;
        GLuint refractionDepthTexture;
    public:
        WaterFrameBuffer() {//call when loading the game
            initialiseReflectionFrameBuffer();
            initialiseRefractionFrameBuffer();
        }

        void cleanUp() {//call when closing the game
            glDeleteFramebuffers(1, &reflectionFrameBuffer);
            glDeleteTextures(1, &reflectionTexture);
            glDeleteRenderbuffers(1, &reflectionDepthBuffer);
            glDeleteFramebuffers(1, &refractionFrameBuffer);
            glDeleteTextures(1, &refractionTexture);
            glDeleteTextures(1, &refractionDepthTexture);
        }

        void bindReflectionFrameBuffer() {//call before rendering to this FBO
            bindFrameBuffer(reflectionFrameBuffer, REFLECTION_WIDTH, REFLECTION_HEIGHT);
        }

        void bindRefractionFrameBuffer() {//call before rendering to this FBO
            bindFrameBuffer(refractionFrameBuffer, REFRACTION_WIDTH, REFRACTION_HEIGHT);
        }

        void unbindCurrentFrameBuffer() {//call to switch to default frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, 1600, 900);
        }

        GLuint getReflectionTexture() {//get the resulting texture
            return reflectionTexture;
        }

        GLuint getRefractionTexture() {//get the resulting texture
            return refractionTexture;
        }

        GLuint getRefractionDepthTexture(){//get the resulting depth texture
            return refractionDepthTexture;
        }

        void initialiseReflectionFrameBuffer() {
            createFrameBuffer(&reflectionFrameBuffer);
            createTextureAttachment(&reflectionTexture, REFLECTION_WIDTH,REFLECTION_HEIGHT);
            createDepthBufferAttachment(&reflectionDepthBuffer, REFLECTION_WIDTH,REFLECTION_HEIGHT);
            unbindCurrentFrameBuffer();
        }

        void initialiseRefractionFrameBuffer() {
            createFrameBuffer(&refractionFrameBuffer);
            createTextureAttachment(&refractionTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT);
            createDepthTextureAttachment(&refractionDepthTexture, REFRACTION_WIDTH,REFRACTION_HEIGHT);
            unbindCurrentFrameBuffer();
        }

        void bindFrameBuffer(int frameBuffer, int width, int height){
            glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
            glViewport(0, 0, width, height);
        }
    private:
        void createFrameBuffer(GLuint * frameBuffer) {
            glGenFramebuffers(1, frameBuffer);
            //generate name for frame buffer
            glBindFramebuffer(GL_FRAMEBUFFER, *frameBuffer);
            //create the framebuffer
            glDrawBuffer(GL_COLOR_ATTACHMENT0);
            //indicate that we will always render to color attachment 0
        }

        void createTextureAttachment(GLuint * texture, int width, int height) {
            glGenTextures(1, texture);
            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, *texture, 0);
        }

        void createDepthTextureAttachment(GLuint * texture, int width, int height){
            glGenTextures(1, texture);
            glBindTexture(GL_TEXTURE_2D, *texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, *texture, 0);
        }

        void createDepthBufferAttachment(GLuint * depthBuffer, int width, int height) {
            glGenRenderbuffers(1, depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, *depthBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, *depthBuffer);
        }
};


#endif //GRAPHICSPROJECT_WATERFRAMEBUFFER_H
