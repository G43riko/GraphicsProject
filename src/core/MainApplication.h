//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINAPPLICATION_H
#define GRAPHICSPROJECT_MAINAPPLICATION_H


#include <src/rendering/Renderer.h>
#include <src/components/terrain/Terrain.h>
#include <src/components/movement/BasicView.h>
#include <src/components/movement/FpsView.h>
#include <src/GUI/BasicGtkGui.h>
#include "BasicApplication.h"

#include <src/rendering/shader/WireframeShader.cpp>
#include <src/rendering/material/TextureManager.h>

class MainApplication : public BasicApplication{
private:
    Renderer  * renderer = nullptr;

//    MainGui gui;

    float time = 0;
    PointerEntity barrel = nullptr;
    PointerEntity teaEntity = nullptr;
    PointerMaterialedModel ball = nullptr;
    PointerTexture2D particleTexture;
public:
    Scene * scene = nullptr;
    Renderer * getMainRenderer(void){
        return renderer;
    }
    void loadContent() override {
        DEBUG("načítavam content");
        auto skyTexture = TextureManager::createCubeTexture("sky");
        scene->setSky(skyTexture);

        particleTexture = TextureManager::createTexture2D("res/textures/particle_1.png");
        auto diffuse = TextureManager::createTexture2D("res/textures/texture.png");
        auto normal = TextureManager::createTexture2D("res/textures/textureNormal.png");
        auto rawModel = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/box.obj"));
        auto plane = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
        auto sphere = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj"));
        auto green = TextureManager::createTexture2D("res/textures/green.png");
        auto tea = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/tea.obj"));

        auto teaMaterial = createMaterial(green);
        auto teaModel = createMaterialedModel(tea, teaMaterial);
        auto material = createMaterial(diffuse, normal);

        ball = createMaterialedModel(sphere, material);
        auto model = createMaterialedModel(rawModel, material);
        auto floor = createMaterialedModel(plane, createMaterial(diffuse, normal));
        auto barrelModel = createMaterialedModel("barrel", getLoader());


        teaEntity = createEntity(teaModel, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        teaMaterial -> setEnvironmentalMap(skyTexture);

        scene -> addEntity(teaEntity);
        barrel = createEntity(barrelModel, Vector3f(0, 4, 0), Vector3f(0.0f, 0.0f, (float)(M_PI / 2)), Vector3f(0.1f, 1.0f, 0.1f));
        scene -> addEntity(barrel);

        scene -> addEntity(createEntity(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        scene -> addEntity(createEntity(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        scene -> addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        scene -> addEntity(createEntity(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        scene -> addEntity(createEntity(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));


        Terrain t = Terrain(getLoader(), diffuse, 100, 128, 5, 40);
        scene -> addEntity(createEntity(t.getModel(), Vector3f(-50, 1, -50), Vector3f(0.0f), Vector3f(1.0f)));
    }

    void init(void) override {
        DEBUG("MainApplication::init - start: " << glfwGetTime());
//        gui.init();

        renderer = new Renderer(getLoader(), WindowManager::width, WindowManager::height);
        DEBUG("MainApplication::init - after  new Renderer: " << glfwGetTime());
        scene = new Scene(getLoader());
        DEBUG("MainApplication::init - after  new Scene: " << glfwGetTime());



        auto screen = Screen(WindowManager::width, WindowManager::height, getLoader());
        DEBUG("MainApplication::init - after  auto screen = Screen: " << glfwGetTime());
        PointerPointLight sun = createPointLight(Vector3f(100000, 100000, -100000), Vector3f(1.3f, 1.3f, 1.3f), Vector3f(1.0f, 0.0f, 0.0f));
        PointerPointLight light = createPointLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
        PointerPointLight light1 = createPointLight(Vector3f(200, 10, 200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

        scene -> addLight(sun);
        renderer -> setSun(sun);

//        renderer -> setPostFx(true);

        setView(new FpsView(renderer -> getActualCamera(), true));
        DEBUG("MainApplication::init - end: " << glfwGetTime());
    };
    void update(float delta) override {
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = EQ(delta, 1.0f) ? 0.2f : 1.0f;
        }
        barrel -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.05f, 0.0f) * delta);
        teaEntity -> getTransform() -> getRotation() -> rotate(Vector3f(0.0f, 0.005f, 0.0f) * delta);

        renderer -> prepareRenderer(0, 0, 0, 1);
        time += 0.02f * delta;
        renderer -> init3D();
        scene -> update(delta);
        getView().update(delta);
        renderer -> input();
        renderer -> update(delta);
        if(Input::isKeyDown(GLFW_KEY_F)){
            scene -> createParticle(particleTexture, Vector3f(0.0f, 2.0f, -2.0f), Vector3f(random(-0.02, 0.02), random(0.01, 0.1), random(-0.02, 0.02)), 0, 100, 0, 1);
        }

        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            //glfwSetWindowShouldClose(WindowManager::window, 1);
            stop();
        }

        if(Input::getMouseDown(0)){
            PointerGameObject entity = PointerGameObject(new GameObject(createEntity(ball, renderer -> getActualCamera() -> position, Vector3f(), Vector3f(1))));
            entity->setVelocity(renderer->getActualCamera() ->getForward());
            scene->addObject(entity);
        }
    };

    void onSecondElapse(int fps) override{
//        printf("FPS: %d\n", fps);
    };
    void render(void) override {

        renderer -> renderScene(*scene);
//        renderer -> renderSceneDeferred(*scene);
    };
    void cleanUp(void) override {
        localCleanUp();
        DEBUG("maže sa renderer v main application");
        getLoader().cleanUp();
//        ContentLoader::clearTextures();
        TextureManager::cleanUp();
        renderer -> cleanUp();
        delete renderer;
        renderer = nullptr;

        scene -> cleanUp();
        delete scene;
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
