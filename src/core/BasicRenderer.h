//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICRENDERER_H
#define GRAPHICSPROJECT_BASICRENDERER_H


#include <src/components/lights/DirectionalLight.h>
#include <src/components/lights/PointLight.h>
#include <src/rendering/RenderUtil.h>
#include <src/core/BasicCamera.h>
#include <src/core/BasicScene.h>
#include <src/components/Master.h>

class Master;

class BasicRenderer {
protected:
    Master master;
    PointerPointLight sun = nullptr;
    PointerCamera actualCamera = nullptr;
public:
    virtual ~BasicRenderer(){};
    virtual void init3D(void) = 0;
    virtual void prepareRenderer(GLfloat red  = 0, GLfloat green  = 0, GLfloat blue  = 0, GLfloat alpha = 1) = 0;
    virtual void update(float delta) = 0;
    virtual void input(void) = 0;
    virtual void cleanUp(void) = 0;
    virtual void addTexture(GuiTexture texture) = 0;
    //RENDERERS
    virtual void renderSceneDeferred(BasicScene * scene) = 0;
    virtual void renderScene(BasicScene * scene) = 0;

    //GETTERS
    inline Master * getMaster(void){ return &master; }
    inline PointerCamera getActualCamera(void){ return actualCamera; };
    inline void setSun(PointerPointLight sun){ this -> sun = sun; };
};

#endif //GRAPHICSPROJECT_BASICRENDERER_H
