//
// Created by gabriel on 15.10.2016.
//

#include "Fbo.h"

int Fbo::NONE = 0;
int Fbo::DEPTH_TEXTURE = 1;
int Fbo::DEPTH_RENDER_BUFFER = 2;

GLuint Fbo::depthBuffer;
GLuint Fbo::colourBuffer;
GLuint Fbo::colourBuffer2;