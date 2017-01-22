//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICENGINE_H
#define GRAPHICSPROJECT_BASICENGINE_H


#include <src/GUI/BasicGtkGui.h>
#include "BasicApplication.h"
#include "MainApplication.h"

class BasicEngine {
    private:
        long fpsCounter = 0;
        BasicApplication * app = nullptr;
        Loader * loader = new Loader();
        BasicGtkGui gui = BasicGtkGui(this);
        bool running = false;
        int width;
        int height;

        void cleanUp(void){
            showStatus();

            loader -> cleanUp();
            delete loader;
        };

        void init(void){
            printf("BasicEngine::init - start: %lf\n", glfwGetTime());
            gui.init();
//            WindowManager::init(width, height, "GEngine", false);
//            Input::init(WindowManager::window, WindowManager::width, WindowManager::height);
//
//            app -> setLoader(&loader);
//            app -> init();
//            app -> loadContent();
//
//            app -> start();
//
//            gui.setWater(new GtkWater(((MainApplication * )app)->getMainRenderer()->getWaterMaster()));
//            gui.setPostFx(new GtkPostFx(((MainApplication * )app) ->getMainRenderer()->getPostFxMaster()));
//            gui.setRenderer(new GtkRenderer(((MainApplication * )app) ->getMainRenderer()));
            printf("BasicEngine::init - end: %lf\n", glfwGetTime());
        };

        void showStatus(void){
            printf("frames: %ld, elapsedTime: %lf\n", fpsCounter, glfwGetTime());
        }

        void update(float delta){
            fpsCounter++;

            if(running){
                app -> update(delta);
                app -> render();
            }
            if(Input::getKeyDown(GLFW_KEY_M)){
                gui.showWater();
            }
            if(Input::getKeyDown(GLFW_KEY_N)){
                gui.showPostFx();
            }
            if(Input::getKeyDown(GLFW_KEY_B)){
                gui.showRenderer();
            }
//            if(Input::getKeyDown(GLFW_KEY_V)){
//                gui.showScene();
//            }

            gui.update();
            Input::update();
            WindowManager::update();
        };
    public:
        void appStart(void){
            WindowManager::init(width, height, "GEngine", false);
            Input::init(WindowManager::window, WindowManager::width, WindowManager::height);
            if(!loader){
                printf("nieje loader\n");
            }
            else{
                printf("je loader\n");
            }

            app -> setLoader(loader);
            app -> init();
            app -> loadContent();

            app -> start();

            gui.setWater(new GtkWater(((MainApplication * )app)->getMainRenderer()->getWaterMaster()));
            gui.setPostFx(new GtkPostFx(((MainApplication * )app) ->getMainRenderer()->getPostFxMaster()));
            gui.setRenderer(new GtkRenderer(((MainApplication * )app) ->getMainRenderer()));

            running = true;
        };
        void appStop(void){
            running = false;

            app -> cleanUp();
            delete app;
            app = nullptr;
            WindowManager::close();
        };

        void setUpApp(BasicApplication * app){
            if(this -> app){
                this -> app -> cleanUp();
                delete this -> app;
            }
            this -> app = app;
        };

        BasicEngine(BasicApplication * app, int width, int height) : app(app), width(width), height(height){
            printf("BasicEngine::BasicEngine %lf\n", glfwGetTime());
        };

        void start(void){
            printf("BasicEngine::start - start: %lf\n", glfwGetTime());
            float delta = 1;
            int fps = 0;


            double currentTime = glfwGetTime();
            init();
            //while (/*running || *//*app -> isRunning() && */!WindowManager::isCloseRequest()) {
            while(!gui.getExitRequest()){
                if(app && running){
                    fps++;
                    if(glfwGetTime() - currentTime > 1.0){
                            app -> onSecondElapse(fps);
                        fps = 0;
                        currentTime = glfwGetTime();
                    }
                    if(WindowManager::isCloseRequest()){
                        appStop();
                    }
                }
                update(delta);
            }
            cleanUp();
            printf("BasicEngine::start - end : %lf\n", glfwGetTime());
        };
};


#endif //GRAPHICSPROJECT_BASICENGINE_H
