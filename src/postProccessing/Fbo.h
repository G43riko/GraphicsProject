//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_FBO_H
#define GRAPHICSPROJECT_FBO_H

#include <src/rendering/material/Texture2D.h>
#include "../rendering/WindowManager.h"

class Fbo {
private :
    bool multisample = false;

    int buffersCount;
    int width;
    int height;

    GLuint frameBuffer;
    GLuint colourTexture;
    GLuint depthTexture;

    GLuint depthBuffer;
    GLuint * colorBuffers;

    void determineDrawBuffer(void);
    void initialiseFrameBuffer(int);
    void createFrameBuffer(void);
    void createMultisampleColorAttachment(GLuint *, int);
    void createTextureAttachment(void);
    void createDepthTextureAttachment(void);
    void createDepthBufferAttachment(void);
public:
    static constexpr int NONE = 0;
    static constexpr int DEPTH_TEXTURE = 1;
    static constexpr int DEPTH_RENDER_BUFFER = 2;

    Fbo(int width, int height) : Fbo(width, height, DEPTH_RENDER_BUFFER, 2){}
    Fbo(int width, int height, int depthBufferType):Fbo(width, height, depthBufferType, 1){}
    Fbo(int width, int height, int depthBufferType, int buffersCount);

    void cleanUp(void);
    void bindFrameBuffer(void);
    void unbindFrameBuffer(void);
    void bindToRead(void);
    void resolveToFbo(GLenum readBuffer, Fbo output);
    void resolveToScreen(void);
    int getColourTexture(void);
    int getDepthTexture(void);
};

#endif //GRAPHICSPROJECT_FBO_H
