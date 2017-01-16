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
//        static inline gpointer loadContent(gpointer user_data){
//            BasicApplication * application = (BasicApplication *)user_data;
//            application -> loadContent();
//        };
        long fpsCounter = 0;
        BasicApplication * app = nullptr;
        Loader loader = Loader();
        BasicGtkGui gui;
        int width;
        int height;

        void cleanUp(void){
            showStatus();
            WindowManager::close();
            loader.cleanUp();
            app -> cleanUp();
            delete app;
        };

        void init(void){
            printf("BasicEngine::init - start: %lf\n", glfwGetTime());
            WindowManager::init(width, height, "GEngine", false);
            printf("BasicEngine::init - after WindowManager::init: %lf\n", glfwGetTime());
            Input::init(WindowManager::window, WindowManager::width, WindowManager::height);
            printf("BasicEngine::init - after Input::init: %lf\n", glfwGetTime());

            app -> setLoader(&loader);
            app -> init();
            printf("BasicEngine::init - before app->loadConntent: %lf\n", glfwGetTime());
            app -> loadContent();
            printf("BasicEngine::init - after app->loadConntent: %lf\n", glfwGetTime());

            gui.init();
            app -> start();
//            GThread * loadContentThread = g_thread_new(NULL, BasicEngine::loadContent, app);
//            g_thread_join(loadContentThread);

//            gui.setScene((new GtkScene(((MainApplication * )app) ->scene)));

            gui.setWater(new GtkWater(((MainApplication * )app)->getMainRenderer()->getWaterMaster()));
//            gui.setPostFx(new GtkPostFx(((MainApplication * )app) ->getMainRenderer()->getPostFxMaster()));
            gui.setRenderer(new GtkRenderer(((MainApplication * )app) ->getMainRenderer()));
            printf("BasicEngine::init - end: %lf\n", glfwGetTime());
        };

        void showStatus(void){
            printf("frames: %ld, elapsedTime: %lf\n", fpsCounter, glfwGetTime());
        }

        void update(float delta){
            fpsCounter++;
            app -> update(delta);
            app -> render();

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
        BasicEngine(BasicApplication * app, int width, int height) : app(app), width(width), height(height){
            printf("BasicEngine::BasicEngine %lf\n", glfwGetTime());
        };

        void start(void){
            printf("BasicEngine::start - start: %lf\n", glfwGetTime());
            float delta = 1;
            int fps = 0;

            double currentTime = glfwGetTime();
            init();
            while (app -> isRunning() && !WindowManager::isCloseRequest()) {
                fps++;
                if(glfwGetTime() - currentTime > 1.0){
                    app -> onSecondElapse(fps);
                    fps = 0;
                    currentTime = glfwGetTime();
                }
                update(delta);
            }
            printf("BasicEngine::start - before cleanUp() : %lf\n", glfwGetTime());
            cleanUp();
            printf("BasicEngine::start - end : %lf\n", glfwGetTime());
        };
};


#endif //GRAPHICSPROJECT_BASICENGINE_H
