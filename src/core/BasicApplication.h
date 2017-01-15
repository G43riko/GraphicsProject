//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICAPPLICATION_H
#define GRAPHICSPROJECT_BASICAPPLICATION_H

#include "BasicRenderer.h"
#include "BasicScene.h"

class BasicApplication{
private:
    bool running = false;
    Loader * loader = nullptr;

    BasicRenderer * renderer = nullptr;
    BasicScene * scene = nullptr;
    BasicView * view = nullptr;
protected:
    void setRenderer(BasicRenderer * renderer){
        if(this -> renderer == nullptr){
            this -> renderer = renderer;
        }
    };
    void setView(BasicView * view){
        if(this -> view == nullptr){
            this -> view = view;
        }
    };
    void setScene(BasicScene * renderer){
        if(this -> scene == nullptr){
            this -> scene = scene;
        }
    };
    void stop(void){
        running = true;
    };

    BasicView& getView(void){
        return *view;
    };
    BasicRenderer *getRenderer(void){
        return renderer;
    };
    BasicScene *getScene(void){
        return scene;
    };
    Loader getLoader(void){
        return *loader;
    };
    void localCleanUp(void){
        if(this -> renderer){
            renderer -> cleanUp();
            delete renderer;
        }
        if(this -> view){
            view -> cleanUp();
            delete view;
        }
        if(this -> scene){
            scene -> cleanUp();
            delete scene;
        }
    };
public:
    virtual ~BasicApplication(){};
    void setLoader(Loader * loader){
        if(this -> loader == nullptr){
            this -> loader = loader;
        }
    };
    bool isRunning(void){
        return running;
    };
    void start(void){
        printf("startujem\n");
        running = true;
    };
    virtual void loadContent(void){};
    virtual void init(void) = 0;
    virtual void update(float delta) = 0;
    virtual void render(void) = 0;
    virtual void cleanUp(void){};
    virtual void onSecondElapse(int fps){};
};

#endif //GRAPHICSPROJECT_BASICAPPLICATION_H
