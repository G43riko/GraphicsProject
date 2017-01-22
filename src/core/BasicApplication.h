//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICAPPLICATION_H
#define GRAPHICSPROJECT_BASICAPPLICATION_H

#include "BasicRenderer.h"
#include "BasicScene.h"
#include <src/components/movement/BasicView.h>

class BasicApplication{
private:
    bool l_running = false;
    Loader * l_loader = nullptr;

    BasicRenderer * l_renderer = nullptr;
    BasicScene * l_scene = nullptr;
    BasicView * l_view = nullptr;
protected:
    void setRenderer(BasicRenderer * l_renderer){
        if(this -> l_renderer == nullptr){
            this -> l_renderer = l_renderer;
        }
    };
    void setView(BasicView * l_view){
        if(this -> l_view == nullptr){
            this -> l_view = l_view;
        }
    };
    void setScene(BasicScene * l_scene){
        if(this -> l_scene == nullptr){
            this -> l_scene = l_scene;
        }
    };
    void stop(void){
        l_running = true;
    };

    BasicView& getView(void){
        return *l_view;
    };
    BasicRenderer *getRenderer(void){
        return l_renderer;
    };
    BasicScene *getScene(void){
        return l_scene;
    };
    Loader getLoader(void){
        return *l_loader;
    };
    void localCleanUp(void){
        if(this -> l_renderer){
            printf("maže sa renderer v basic application\n");
            l_renderer -> cleanUp();
            delete l_renderer;
        }
        if(this -> l_view){
            l_view -> cleanUp();
            delete l_view;
        }
        if(this -> l_scene){
            l_scene -> cleanUp();
            delete l_scene;
        }
    };
public:
    virtual ~BasicApplication(){};
    void setLoader(Loader * loader){
        this -> l_loader = loader;
//        if(this -> loader == nullptr){
//            this -> loader = loader;
//        }
    };
    bool isRunning(void){
        return l_running;
    };
    void start(void){
        printf("startujem\n");
        l_running = true;
    };
    virtual void loadContent(void){};
    virtual void init(void) = 0;
    virtual void update(float delta) = 0;
    virtual void render(void) = 0;
    virtual void cleanUp(void){};
    virtual void onSecondElapse(int fps){};
};

#endif //GRAPHICSPROJECT_BASICAPPLICATION_H
