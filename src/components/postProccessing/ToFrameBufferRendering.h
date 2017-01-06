//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_TOFRAMEBUFFERRENDERING_H
#define GRAPHICSPROJECT_TOFRAMEBUFFERRENDERING_H


#include <src/rendering/material/Texture2D.h>
#include <src/rendering/WindowManager.h>

class ToFrameBufferRendering {
private:
	PointerTexture2D texture;
	GLuint framebufferID;
	GLuint depthRenderBufferID;
	GLuint textureID;

	PointerTexture2D initTexture(int width, int height){
		glGenTextures(1, &textureID);
		PointerTexture2D txt(new Texture2D("FBO", textureID, width, height));

		glBindTexture(GL_TEXTURE_2D, txt -> getTextureID());

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_INT, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, txt -> getTextureID(), 0);
		return txt;
	}
    void initDepthBuffer(int width, int height){
        glGenRenderbuffers(1, &depthRenderBufferID);

        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBufferID);


    }
public:
	ToFrameBufferRendering() : ToFrameBufferRendering(256, 256){}

	ToFrameBufferRendering(int width, int height){
		glGenFramebuffers(1, &framebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

		texture = initTexture(width, height);

		initDepthBuffer(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void startRenderToFrameBuffer(){
		glDepthFunc (GL_LEQUAL);
		glEnable (GL_DEPTH_TEST);
		glShadeModel (GL_SMOOTH);
		glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glViewport(0, 0, texture -> getWidth(), texture -> getHeight());

		glBindTexture(GL_TEXTURE_2D, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void stopRenderToFrameBuffer(){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport (0, 0, WindowManager::width, WindowManager::height);
	}

	void cleanUp() {//call when closing the game
		glDeleteFramebuffers(1, &framebufferID);
		texture -> cleanUp();
		glDeleteRenderbuffers(1, &depthRenderBufferID);
	}

	PointerTexture2D getTexture() {
		return texture;
	}
};


#endif //GRAPHICSPROJECT_TOFRAMEBUFFERRENDERING_H
