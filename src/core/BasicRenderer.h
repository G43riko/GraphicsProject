//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICRENDERER_H
#define GRAPHICSPROJECT_BASICRENDERER_H


#include <src/components/lights/DirectionalLight.h>
#include <src/components/lights/PointLight.h>
#include <src/rendering/RenderUtil.h>
#include <src/utils/Loader.h>
#include "BasicCamera.h"
#include "BasicScene.h"

class BasicRenderer {
private:
    BasicCamera camera;
    PointerDirectionalLight sun = nullptr;
    Vector3f ambientColor = Vector3f(DEFAULT_AMBIENT_RED, DEFAULT_AMBIENT_GREEN, DEFAULT_AMBIENT_BLUE);
    RenderUtil utils;
    int options = 0;
protected:
    void turnOnOption(unsigned char val){
        options |= val;
    }
    void turnOffOption(unsigned char val){
        options &= ~val;
    }
    void toggleOption(unsigned char val){
        options ^= val;
    }
    bool getOption(unsigned char val){
        return (char)options & val;
    }
public:
    virtual ~BasicRenderer(){};
    virtual void prepareRenderer(GLfloat red    = DEFAULT_BACKGROUND_RED,
                                 GLfloat green  = DEFAULT_BACKGROUND_GREEN,
                                 GLfloat blue   = DEFAULT_BACKGROUND_BLUE,
                                 GLfloat alpha  = DEFAULT_BACKGROUND_ALPHA){
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };
    void setCamera(BasicCamera camera){
        this -> camera = camera;
    };
    void setAmbientColor(Vector3f color){
        ambientColor = color;
    };
    void setSun(PointerDirectionalLight sun){
        this -> sun = sun;
    };
    virtual void init3D(void){
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    };
    BasicCamera getActualCamera(void){
        return camera;
    };
    virtual void renderSceneForward(BasicScene * scene) = 0;
    virtual void renderSceneDeferred(BasicScene * scene) = 0;
    virtual void input(void) = 0;
    virtual void update(float delta) = 0;
    virtual void init(void) = 0;
    virtual void cleanUp(void) = 0;
};

#endif //GRAPHICSPROJECT_BASICRENDERER_H
