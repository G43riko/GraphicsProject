//
// Created by gabriel on 15.10.2016.
//

#include "Fbo.h"

Fbo::Fbo(int width, int height, int depthBufferType, int buffersCount) {
    this -> width = width;
    this -> height = height;
    this -> buffersCount = buffersCount;
    colorBuffers = new GLuint[buffersCount];
    multisample = buffersCount > 1;
    initialiseFrameBuffer(depthBufferType);
}


void Fbo::cleanUp(void) {
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteTextures(1, &colourTexture);
    glDeleteTextures(1, &depthTexture);
    glDeleteRenderbuffers(1, &depthBuffer);
    for(unsigned int i=0 ; i<buffersCount ; i++)
        glDeleteRenderbuffers(1, &colorBuffers[i]);
    delete[] colorBuffers;

//        glDeleteRenderbuffers(1, &colourBuffer);
//        glDeleteRenderbuffers(1, &colourBuffer2);//TODO nahradiť vectorom
}

void Fbo::bindFrameBuffer(void) {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, width, height);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Fbo::unbindFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, WindowManager::width, WindowManager::height);
}

void Fbo::bindToRead(void) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
}


void Fbo::resolveToFbo(GLenum readBuffer, Fbo output){
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, output.frameBuffer);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
    glReadBuffer(readBuffer);
    glBlitFramebuffer(0, 0, width, height, 0, 0, output.width, output.height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    unbindFrameBuffer();
}
void Fbo::resolveToScreen(void){
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
    glReadBuffer(GL_COLOR_ATTACHMENT0);//toto som sem pridal aby sa vždy prepol na GL_COLOR_ATTACHMENT0 pri vykreslovaní sceny
    glDrawBuffer(GL_BACK);
    glBlitFramebuffer(0, 0, width, height,  0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    unbindFrameBuffer();
}

GLuint Fbo::getColourTexture(void) {
    return colourTexture;
}

GLuint Fbo::getDepthTexture(void) {
    return depthTexture;
}

void Fbo::determineDrawBuffer(void){
    std::vector<GLenum> buffer;
    for(unsigned int i=0 ; i<buffersCount ; i++)
        buffer.push_back(GL_COLOR_ATTACHMENT0 + i);
    glDrawBuffers(static_cast<int>(buffer.size()), buffer.data());
}

void Fbo::initialiseFrameBuffer(int type) {
    createFrameBuffer();
    if(multisample){
        for(unsigned int i=0 ; i<buffersCount ; i++)
            createMultisampleColorAttachment(&colorBuffers[i], GL_COLOR_ATTACHMENT0 + i);
    }
    else
        createTextureAttachment();

    if (type == DEPTH_RENDER_BUFFER)
        createDepthBufferAttachment();
    else if (type == DEPTH_TEXTURE)
        createDepthTextureAttachment();
    unbindFrameBuffer();
}

void Fbo::createFrameBuffer(void) {
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    determineDrawBuffer();
}

void Fbo::createMultisampleColorAttachment(GLuint * buffer, GLuint attach){
    glGenRenderbuffers(1, buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, *buffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGBA8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attach, GL_RENDERBUFFER, *buffer);
}

void Fbo::createTextureAttachment(void) {
    glGenTextures(1, &colourTexture);
    glBindTexture(GL_TEXTURE_2D, colourTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colourTexture, 0);
}

void Fbo::createDepthTextureAttachment(void) {
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
}

void Fbo::createDepthBufferAttachment(void) {
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    if(multisample)
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT24, width, height);//TODO tu je namiesto 24 16
    else
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
}