//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICENGINE_H
#define GRAPHICSPROJECT_BASICENGINE_H


#include <src/GUI/MainGui.h>
#include "BasicApplication.h"
#include "MainApplication.h"

class BasicEngine {
    private:
        static inline gpointer loadContent(gpointer user_data){
            BasicApplication * application = (BasicApplication *)user_data;
            application -> loadContent();
        };
        long fpsCounter = 0;
        BasicApplication * app = nullptr;
        Loader loader = Loader();
        MainGui gui;
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
            WindowManager::init(width, height, "GEngine", false);
            Input::init(WindowManager::window, WindowManager::width, WindowManager::height);

            app -> setLoader(&loader);
            app -> init();

//            app -> loadContent();

            gui.init();
            app -> start();
//            GThread * loadContentThread = g_thread_new(NULL, BasicEngine::loadContent, app);
//            g_thread_join(loadContentThread);
            gui.setWater(new GtkWater(((MainApplication * )app)->getMainRenderer()->getWater()));

        };

        void showStatus(void){
            printf("frames: %ld, elapsedTime: %lf\n", fpsCounter, glfwGetTime());
        }

        void update(float delta){
            fpsCounter++;
            app -> update(delta);
            app -> render();

            gui.update();
            Input::update();
            WindowManager::update();
        };
    public:
        BasicEngine(BasicApplication * app, int width, int height) : app(app), width(width), height(height){
        };

        void start(void){
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
            cleanUp();
        };
};


#endif //GRAPHICSPROJECT_BASICENGINE_H
