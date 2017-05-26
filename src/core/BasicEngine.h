//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICENGINE_H
#define GRAPHICSPROJECT_BASICENGINE_H

#include <memory>
#include <vector>
#include <time.h>

#include <chrono>

#include <src/core/BasicApplication.h>

class BasicEngine {
private:
    long _fpsCounter        = 0;
    BasicApplication * _app = nullptr;
    Loader _loader          = Loader();
    BasicGtkGui _gui        = BasicGtkGui(this);
    bool _running           = false;
    bool _showGui           = true;
    const int _width;
    const int _height;

    /**
     * Funckia vyčistí celý engine
     */
    inline void cleanUp(void){
        showStatus();
    };

    /**
     * Funckia inicializuje všetko potrebné pre beh enginu
     */
    inline void init(void){
        DEBUG("BasicEngine::init - start: " << glfwGetTime());

        if(_showGui){
            _gui.init();
        }
        else{
            appStart();
        }

        DEBUG("BasicEngine::init - end: " << glfwGetTime());
    };

    /**
     * Funkcia vypíše priebežný stav enginu
     */
    inline void showStatus(void) const {
        DEBUG("frames: " << _fpsCounter << ", elapsedTime: " << glfwGetTime());
    }

    /**
     * Funckia vykoná update enginu
     *
     * @param i_delta - časový koeficient podla aktuálneho FPS
     */
    inline void update(const float i_delta){
        _fpsCounter++;

        //double renderTime, updateTime;
        if(_running){
//            updateTime = glfwGetTime();
            _app -> update(i_delta);
//            printf("update: %f ", glfwGetTime() - updateTime);
//            renderTime = glfwGetTime();
            _app -> render();
//            printf("render: %f ", glfwGetTime() - renderTime);
        }
        if(_showGui){
            if(Input::getKeyDown(GLFW_KEY_M)){
                _gui.showWater();
            }
            if(Input::getKeyDown(GLFW_KEY_N)){
                _gui.showPostFx();
            }
            if(Input::getKeyDown(GLFW_KEY_B)){
                _gui.showRenderer();
            }
            //            if(Input::getKeyDown(GLFW_KEY_V)){
            //                gui.showScene();
            //            }

            _gui.update();
        }
//        updateTime = glfwGetTime();
        Input::update();
        WindowManager::update();
//        printf("update2: %f \n", glfwGetTime() - updateTime);
    };
public:
    inline BasicEngine(BasicApplication * i_app, int i_width, int i_height) : _app(i_app), _width(i_width), _height(i_height){
        DEBUG("BasicEngine::BasicEngine" << glfwGetTime());
        _showGui = _app == nullptr;
    };

    /**
     * Funkcia spusti aktuálne nastavenú aplikáciu v engine
     */
    inline void appStart(void){
        //inicializujem okno
        if(_showGui){
            WindowManager::init(_gui.getResX(), _gui.getResY(), DEFAULT_TITLE, _gui.getFullscreen());
        }
        else{
            WindowManager::init(0, 0 , DEFAULT_TITLE, true);
        }
        //inicializujem input
        Input::init(WindowManager::width, WindowManager::height);

        //pridám aplikacii loader
        _app -> setLoader(&_loader);

        if(_showGui){
            //v gui zmením tlačítka
            _gui.appIsRunning(true);

            //inicializujeme aplikáciu
            _app -> init(&_gui);
        }
        else{
            _app -> init(nullptr);
        }

        //načítame potrebný obsah
        _app -> loadContent();

        //spustime aplikáciu
        _app -> start();

        //nastavím engine aby updatoval aj aplikáciu
        _running = true;
    };

    /**
     * Funkcia zastaví aktuálne bežiacu aplikáciu
     */
    inline void appStop(void){
        if(_showGui){
            //v gui zmením tlačítka
            _gui.appIsRunning(false);
        }
        //nastavím engine aby neupdatoval aplikáciu
        _running = false;

        //upraceme aplikáciu
        _app -> localCleanUp();
        _app -> cleanUp();
        delete _app;
        _app = nullptr;

        //zavrieme okno
        WindowManager::close();
    };

    /**
     * Funckia nastaví aplikáciu do enginu
     *
     * @param i_app - aplikácia ktorá sa bude spúštať
     */
    inline void setUpApp(BasicApplication * i_app){
        //zmažeme staru aplikáciu ak existovala
        if(this -> _app){
            ERROR("nemožeš zapnuť aplikáciu keď už jedna je spustená!!! ...najprv ju musíš vypnuť");
            return;
        }

        //vytvorime novu
        this -> _app = i_app;
    };

    /**
     * Funkcia sa zavolá len raz a spustí celý engine
     */
    inline void start(void){
        const uint FPS = 30, frameTime = 1000000 / FPS;
        uint fps;
        auto start = std::chrono::high_resolution_clock::now();
        auto startLoopTime = start, middleLoopTime = start, endLoopTime = start;
        float delta = 1;
        long long microseconds, loopTime;

        init();
        while((_showGui && !_gui.getExitRequest()) || (!_showGui && _running)){
            fps = 0;
            start = std::chrono::high_resolution_clock::now();
            do{
                startLoopTime = std::chrono::high_resolution_clock::now();
                //UPDATE
                fps++;
                if(_running){
                    if(WindowManager::isCloseRequest() || !_app -> isRunning()){
                        appStop();
                    }
                }
                update(delta);

                //////////SYS
                middleLoopTime = std::chrono::high_resolution_clock::now();
                loopTime = std::chrono::duration_cast<std::chrono::microseconds>(middleLoopTime - startLoopTime).count();
                if(loopTime <= frameTime){
                    usleep((uint)(frameTime - loopTime));
                }
                endLoopTime = std::chrono::high_resolution_clock::now();
                microseconds = std::chrono::duration_cast<std::chrono::microseconds>(endLoopTime - start).count();

                delta = (float)frameTime /  (float)std::chrono::duration_cast<std::chrono::microseconds>(endLoopTime - startLoopTime).count();

            } while(microseconds < 1000000);
            if(_running){
                _app -> onSecondElapse(fps);
            }
        }
        cleanUp();
    }
    inline void start2(void){
        DEBUG("BasicEngine::start - start: " << glfwGetTime());
        double currentTime  = glfwGetTime();
        float delta         = 1;
        int fps             = 0;
        init();
        while((_showGui && !_gui.getExitRequest()) || (!_showGui && _running)){
            if(_running){
                fps++;
                if(glfwGetTime() - currentTime > 1.0){
                    _app -> onSecondElapse(fps);
                    fps = 0;
                    currentTime = glfwGetTime();
                }
                if(WindowManager::isCloseRequest() || !_app -> isRunning()){
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
    inline int getResX(void) const{return _width;}

    /**
     * Funkcia vráti výšku okna aktuálnej aplikácie
     *
     * @return - výška okna aktuálnej aplikácie v pixeloch
     */
    inline int getResY(void) const{return _height;}

};

#endif //GRAPHICSPROJECT_BASICENGINE_H
