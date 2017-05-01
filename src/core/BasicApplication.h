//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICAPPLICATION_H
#define GRAPHICSPROJECT_BASICAPPLICATION_H

#include <src/core/BasicRenderer.h>
#include <src/GUI/BasicGtkGui.h>
#include <src/components/movement/BasicView.h>

class BasicApplication{
private:
    bool l_running              = false;
    BasicRenderer * l_renderer  = nullptr;
    BasicScene * l_scene        = nullptr;
    BasicView * l_view          = nullptr;
    Loader * l_loader           = nullptr;

protected:

    inline void setRenderer(BasicRenderer * i_renderer){
        SET_IF_IS_NULL(l_renderer, i_renderer);
    };
    inline void setView(BasicView * i_view){
        SET_IF_IS_NULL(l_view, i_view);
    };
    inline void setScene(BasicScene * i_scene){
        SET_IF_IS_NULL(l_scene, i_scene);
    };
    inline void stop(void){
        l_running = false;
    };

    inline BasicView& getView(void) const{return *l_view; };
    inline BasicRenderer *getRenderer(void)const{return l_renderer; };
    inline BasicScene *getScene(void)const{ return l_scene; };
    inline Loader getLoader(void)const{ return *l_loader; };
public:
    inline void localCleanUp(void){
        CHECK_AND_CLEAR(l_renderer);
        CHECK_AND_CLEAR(l_view);
        CHECK_AND_CLEAR(l_scene);
    };

    virtual ~BasicApplication(void){};
    inline void setLoader(Loader * i_loader){ this -> l_loader = i_loader; };
    inline bool isRunning(void) const{return l_running; };
    inline void start(void){
        PRINT("startujem");


        l_running = true;
    };
    virtual void loadContent(void){};

    /**
     * Funkcia inicializuje engine
     *
     * musia sa volať tieto funkcie:
     * 1. setRenderer
     * 2. setScene
     * 3. setView
     *
     * @param gui
     */
    virtual void init(BasicGtkGui * i_gui) = 0;
    virtual void update(float i_delta){};
    virtual void render(void){};
    virtual void cleanUp(void){};
    virtual void onSecondElapse(const int i_fps){};
};

#endif //GRAPHICSPROJECT_BASICAPPLICATION_H
