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
    PointerPointLight light = nullptr;
    PointerDirectionalLight sun = nullptr;
    PointerCamera actualCamera = nullptr;
public:
    virtual ~BasicRenderer(void){};
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
    inline Master& getMaster(void) {return master; };
    inline PointerCamera getActualCamera(void) const{return actualCamera; };
    inline PointerPointLight getLight(void) const{return light;};
    inline PointerDirectionalLight getSun(void) const{return sun; };

    inline void setSun(PointerDirectionalLight sun){this -> sun = sun; };
    inline void setLight(PointerPointLight light){this -> light = light; };
};

#endif //GRAPHICSPROJECT_BASICRENDERER_H
