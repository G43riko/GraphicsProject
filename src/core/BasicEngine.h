//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICENGINE_H
#define GRAPHICSPROJECT_BASICENGINE_H

#include <memory>
#include <vector>
#include <time.h>

#include <src/core/BasicApplication.h>

class BasicEngine {
    private:
        long l_fpsCounter         = 0;
        BasicApplication * l_app  = nullptr;
        Loader * l_loader         = new Loader();
        BasicGtkGui l_gui         = BasicGtkGui(this);
        bool l_running            = false;
        bool l_showGui            = true;
        int l_width;
        int l_height;

        /**
         * Funckia vyčistí celý engine
         */
        void cleanUp(void){
            showStatus();

            l_loader -> cleanUp();
            delete l_loader;
        };

        /**
         * Funckia inicializuje všetko potrebné pre beh enginu
         */
        void init(void){
            DEBUG("BasicEngine::init - start: " << glfwGetTime());

            if(l_showGui){
                l_gui.init();
            }
            else{
                appStart();
            }

            DEBUG("BasicEngine::init - end: " << glfwGetTime());
        };

        /**
         * Funkcia vypíše priebežný stav enginu
         */
        void showStatus(void){
            DEBUG("frames: " << l_fpsCounter << ", elapsedTime: " << glfwGetTime());
        }

        /**
         * Funckia vykoná update enginu
         *
         * @param i_delta - časový koeficient podla aktuálneho FPS
         */
        void update(float i_delta){
            l_fpsCounter++;

            if(l_running){
                l_app -> update(i_delta);
                l_app -> render();
            }
            if(l_showGui){
                if(Input::getKeyDown(GLFW_KEY_M)){
                    l_gui.showWater();
                }
                if(Input::getKeyDown(GLFW_KEY_N)){
                    l_gui.showPostFx();
                }
                if(Input::getKeyDown(GLFW_KEY_B)){
                    l_gui.showRenderer();
                }
    //            if(Input::getKeyDown(GLFW_KEY_V)){
    //                gui.showScene();
    //            }

                l_gui.update();
            }
            Input::update();
            WindowManager::update();
        };
    public:
        BasicEngine(BasicApplication * i_app, int i_width, int i_height) : l_app(i_app), l_width(i_width), l_height(i_height){
            DEBUG("BasicEngine::BasicEngine" << glfwGetTime());
            l_showGui = l_app == nullptr;
        };

        /**
         * Funkcia spusti aktuálne nastavenú aplikáciu v engine
         */
        void appStart(void){
            //inicializujem okno
            if(l_showGui){
                WindowManager::init(l_gui.getResX(), l_gui.getResY(), DEFAULT_TITLE, l_gui.getFullscreen());
            }
            else{
                WindowManager::init(0, 0 , DEFAULT_TITLE, true);
            }
            //inicializujem input
            Input::init(WindowManager::width, WindowManager::height);

            //pridám aplikacii loader
            l_app -> setLoader(l_loader);

            if(l_showGui){
                //v gui zmením tlačítka
                l_gui.appIsRunning(true);

                //inicializujeme aplikáciu
                l_app -> init(&l_gui);
            }
            else{
                l_app -> init(nullptr);
            }

            //načítame potrebný obsah
            l_app -> loadContent();

            //spustime aplikáciu
            l_app -> start();

            //nastavím engine aby updatoval aj aplikáciu
            l_running = true;
        };

        /**
         * Funkcia zastaví aktuálne bežiacu aplikáciu
         */
        void appStop(void){
            if(l_showGui){
                //v gui zmením tlačítka
                l_gui.appIsRunning(false);
            }
            //nastavím engine aby neupdatoval aplikáciu
            l_running = false;

            //upraceme aplikáciu
            l_app -> localCleanUp();
            l_app -> cleanUp();
            delete l_app;
            l_app = nullptr;

            //zavrieme okno
            WindowManager::close();
        };

        /**
         * Funckia nastaví aplikáciu do enginu
         *
         * @param i_app - aplikácia ktorá sa bude spúštať
         */
        void setUpApp(BasicApplication * i_app){
            //zmažeme staru aplikáciu ak existovala
            if(this -> l_app){
                ERROR("nemožeš zapnuť aplikáciu keď už jedna je spustená!!! ...najprv ju musíš vypnuť");
                return;
            }

            //vytvorime novu
            this -> l_app = i_app;
        };

        /**
         * Funkcia sa zavolá len raz a spustí celý engine
         */
        void start(void){
            DEBUG("BasicEngine::start - start: " << glfwGetTime());
            double currentTime  = glfwGetTime();
            float delta         = 1;
            int fps             = 0;

            init();
            while((l_showGui && !l_gui.getExitRequest()) || (!l_showGui && l_running)){
                if(l_running){
                    fps++;
                    if(glfwGetTime() - currentTime > 1.0){
                        l_app -> onSecondElapse(fps);
                        fps = 0;
                        currentTime = glfwGetTime();
                    }
                    if(WindowManager::isCloseRequest() || !l_app -> isRunning()){
                        appStop();
                    }
                }
                update(delta);
            }
            cleanUp();
            DEBUG("BasicEngine::start - end : " << glfwGetTime());
        };

        /**
         * Funkcia vráti šírku okna aktuálnej aplikácie
         *
         * @return - šírka okna aktuálnej aplikácie v pixeloch
         */
        inline int getResX(void){return l_width;}

        /**
         * Funkcia vráti výšku okna aktuálnej aplikácie
         *
         * @return - výška okna aktuálnej aplikácie v pixeloch
         */
        inline int getResY(void){return l_height;}
};


#endif //GRAPHICSPROJECT_BASICENGINE_H
