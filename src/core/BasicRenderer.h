//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICRENDERER_H
#define GRAPHICSPROJECT_BASICRENDERER_H

#include <src/components/Master.h>

class BasicRenderer {
protected:
    Master master;
    PointerPointLight light = nullptr;
    PointerDirectionalLight sun = nullptr;
    PointerCamera actualCamera = nullptr;
    std::vector<GuiTexture *> textures;
public:
    virtual ~BasicRenderer(void){};
    virtual void init3D(void) = 0;
    virtual void prepareRenderer(const float red  = 0,
                                 const float green  = 0,
                                 const float blue  = 0,
                                 const float alpha = 1) = 0;
    virtual void update(const float delta) = 0;
    virtual void input(void) = 0;
    virtual void cleanUp(void) = 0;
    inline void addTexture(GuiTexture * texture){
        textures.push_back(texture);
    }
    //RENDERERS
//    virtual void renderSceneDeferred(BasicScene * scene) = 0;
    virtual void renderScene(BasicScene * scene) = 0;

    //GETTERS
    inline Master& getMaster(void) {return master; };
    inline PointerCamera getActualCamera(void) const{return actualCamera; };
    inline PointerPointLight getLight(void) const{return light;};
    inline PointerDirectionalLight getSun(void) const{return sun; };

    inline void setSun(PointerDirectionalLight sun){CHECK_AND_SET(this -> sun, sun); };
    inline void setLight(PointerPointLight light){CHECK_AND_SET(this -> light, light); };
};

#endif //GRAPHICSPROJECT_BASICRENDERER_H
