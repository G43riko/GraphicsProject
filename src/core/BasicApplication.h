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
    bool _running              = false;
    BasicRenderer * _renderer  = nullptr;
    BasicScene * _scene        = nullptr;
    BasicView * _view          = nullptr;
    Loader * _loader           = nullptr;

protected:

    inline void setRenderer(BasicRenderer * i_renderer){
        SET_IF_IS_NULL(_renderer, i_renderer);
    };
    inline void setView(BasicView * i_view){
        SET_IF_IS_NULL(_view, i_view);
    };
    inline void setScene(BasicScene * i_scene){
        SET_IF_IS_NULL(_scene, i_scene);
    };
    inline void stop(void){
        _running = false;
    };

    inline BasicView& getView(void) const{return *_view; };
    inline BasicRenderer& getRenderer(void)const{return *_renderer; };
    inline BasicScene *getScene(void)const{ return _scene; };
    inline Loader getLoader(void)const{ return *_loader; };

public:
    inline void localCleanUp(void){
        CHECK_AND_CLEAR(_renderer);
        CHECK_AND_CLEAR(_view);
        CHECK_AND_CLEAR(_scene);
    };

    virtual ~BasicApplication(void){};
    inline void setLoader(Loader * i_loader){ this -> _loader = i_loader; };
    inline bool isRunning(void) const{return _running; };
    inline void start(void){
        PRINT("startujem");


        _running = true;
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
