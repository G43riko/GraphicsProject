//
// Created by gabriel on 16.7.2017.
//

#ifndef GAMEENGINE_SFMLENGINE_H
#define GAMEENGINE_SFMLENGINE_H

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <stdlib.h>
#include <string>

class SfmlEngine{
    uint _width;
    uint _height;
    std::string _title;
    bool _running = false;
    bool _fullscreen = false;
    uint _FPS = 30;
    sf::RenderWindow * _window;
    bool _vsync = false;

    BasicApplication * _app = nullptr;
    Loader _loader          = Loader();

    inline void init(){

        _app -> setLoader(&_loader);
        _app -> init(nullptr);
        _app -> loadContent();
        _app -> start();
    }

    inline void update(float i_delta){
        _app -> update(i_delta);
        _app -> render();
    }
    inline void cleanUp(void){
        CHECK_AND_CLEAR(_app);
    };
    inline void createWindow(void){
        sf::ContextSettings settings(24, 8, 0, 4, 3, settings.Core);


        WindowManager::width = _width;
        WindowManager::height = _height;
        settings.depthBits          = DEPTH_BITS;
        settings.stencilBits        = STENCIL_BITS;
        settings.antialiasingLevel  = ANTI_ALIASING_LEVEL;
        settings.majorVersion       = CONTENT_ATTRIBUTES_MAJOR_VERSION;

        settings.minorVersion       = CONTENT_ATTRIBUTES_MINOR_VERSION;

        if(_fullscreen){
            _window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), _title, sf::Style::Fullscreen, settings);
        }
        else{
            _window = new sf::RenderWindow(sf::VideoMode(_width, _height), _title, sf::Style::Close, settings);
        }
        _window -> setFramerateLimit(_FPS);

        _window -> setActive(true);
        _window -> setVerticalSyncEnabled(_vsync);

    }
public:


    inline SfmlEngine(BasicApplication * app, uint width, uint height, std::string title) :
            _width(width),
            _height(height),
            _app(app),
            _title(title){
    }

    inline void start(void){
        _running = true;
        createWindow();

        glewExperimental = GL_TRUE;
        glewInit();
        if (!glewIsSupported("GL_VERSION_4_3")) {
            ERROR(ERROR_INITIAL_GLEW);
//            glfwTerminate();
            return;
        }
        printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

        sf::Font font;
        if (!font.loadFromFile("res/textures/fonts/arial.ttf")) {
            printf("nepodarilo sa nacitat font");
        }

        sf::Text text;
        text.setFont(font);
        text.setString("Hello world");
        text.setCharacterSize(24);
        text.setColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        init();
        sf::Clock clock;

        while(_running) {
            sf::Event event;
            while (_window -> pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _running = false;
                }
                else if (event.type == sf::Event::Resized) {
                    glViewport(0, 0, event.size.width, event.size.height);
                }
            }

            // clear the buffers
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // draw...
//            double delta =  clock.restart().asSeconds();


//            update(1.0f);

//            _window -> pushGLStates();
            _window -> resetGLStates();
            _window -> draw(text);
            // end the current frame (internally swaps the front and back buffers)
            _window -> display();
        }

        _window -> close();
        cleanUp();
        delete _window;
    }
};

#endif //GAMEENGINE_SFMLENGINE_H
