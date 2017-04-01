//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICENGINE_H
#define GRAPHICSPROJECT_BASICENGINE_H

#include <memory>
#include <vector>

#include <src/rendering/WindowManager.h>
#include <src/utils/Input.h>
#include <src/rendering/Renderer.h>
#include <src/rendering/model/Mesh.h>
#include <src/utils/Loader.h>
#include <src/components/postProccessing/Screen.h>

#include <src/components/postProccessing/Fbo.h>
#include <src/components/postProccessing/PostProccessing.h>
#include <src/components/water/WaterFrameBuffer.h>
#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include <src/components/movement/TopView.h>
#include <src/game/Ball.h>
#include <src/rendering/material/Material.h>
#include <time.h>
#include <src/game/Environment.h>
#include <src/game/Arrow.h>
#include <src/components/shadows/ShadowMaster.h>
#include <src/components/terrain/HeightGenerator.h>
#include <src/components/entities/EntityManager.h>
#include <src/components/particles/ParticleManager.h>
#include <src/core/MainApplication.h>
#include <src/GUI/BasicGtkGui.h>
#include <src/utils/Vectors.h>
#include <src/rendering/material/Texture2D.h>

#include <src/GUI/BasicGtkGui.h>
#include "BasicApplication.h"
#include "MainApplication.h"

class BasicEngine {
    private:
        long fpsCounter         = 0;
        BasicApplication * app  = nullptr;
        Loader * loader         = new Loader();
        BasicGtkGui gui         = BasicGtkGui(this);
        bool running            = false;
        int width;
        int height;

        void cleanUp(void){
            showStatus();

            loader -> cleanUp();
            delete loader;
        };

        void init(void){
            DEBUG("BasicEngine::init - start: " << glfwGetTime());
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
            DEBUG("BasicEngine::init - end: " << glfwGetTime());
        };

        void showStatus(void){
            DEBUG("frames: " << fpsCounter << ", elapsedTime: " << glfwGetTime());
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
            std::cout << "x: " << gui.getResX() << ", y: " << gui.getResY() << "\n";
            WindowManager::init(gui.getResX(), gui.getResY(), "GEngine", gui.getFullscreen());
            Input::init(WindowManager::window, WindowManager::width, WindowManager::height);

            gui.appIsRunning(true);

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
            gui.appIsRunning(false);
            running = false;

            app -> cleanUp();
            delete app;
            app = nullptr;
            WindowManager::close();
        };

        void setUpApp(BasicApplication * app){
            //zmažeme staru aplikáciu ak existovala
            if(this -> app){
                this -> app -> cleanUp();
                delete this -> app;
            }

            //vytvorime novu
            this -> app = app;
        };

        BasicEngine(BasicApplication * app, int width, int height) : app(app), width(width), height(height){
            DEBUG("BasicEngine::BasicEngine" << glfwGetTime());
        };

        void start(void){
            DEBUG("BasicEngine::start - start: " << glfwGetTime());
            float delta = 1;
            int fps = 0;


            double currentTime = glfwGetTime();
            init();
            while(!gui.getExitRequest()){
                if(app && running){
                    fps++;
                    if(glfwGetTime() - currentTime > 1.0){
                        app -> onSecondElapse(fps);
                        fps = 0;
                        currentTime = glfwGetTime();
                    }
                    if(WindowManager::isCloseRequest() || !app->isRunning()){
                        appStop();
                    }
                }
                update(delta);
            }
            cleanUp();
            DEBUG("BasicEngine::start - end : " << glfwGetTime());
        };
    inline int getResX(void){return width;}
    inline int getResY(void){return height;}
};


#endif //GRAPHICSPROJECT_BASICENGINE_H
