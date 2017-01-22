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

class MainApplication : public BasicApplication{
private:
    Renderer  * renderer = nullptr;

//    MainGui gui;

    float time = 0;
    PointerEntity barrel = nullptr;
    PointerEntity teaEntity = nullptr;
    PointerTexture2D particleTexture;
public:
    Scene * scene = nullptr;
    Renderer * getMainRenderer(void){
        return renderer;
    }
    void loadContent() override {

        printf("načítavam content\n");
        auto skyTexture = ContentLoader::loadCubeTexture("sky");
        scene->setSky(skyTexture);

        particleTexture = ContentLoader::loadTexturePNG("res/textures/particle_1.png");
        auto diffuse = ContentLoader::loadTexturePNG("res/textures/texture.png");
        auto normal = ContentLoader::loadTexturePNG("res/textures/textureNormal.png");
        auto rawModel = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/box.obj"));
        auto plane = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
        auto green = ContentLoader::loadTexturePNG("res/textures/green.png");
        auto tea = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/tea.obj"));

        auto teaMaterial = createMaterial(green);
        auto teaModel = createMaterialedModel(tea, teaMaterial);

        auto model = createMaterialedModel(rawModel, createMaterial(diffuse, normal));
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
        printf("MainApplication::init - start: %lf\n", glfwGetTime());
//        gui.init();

        renderer = new Renderer(getLoader(), WindowManager::width, WindowManager::height);
        printf("MainApplication::init - after  new Renderer: %lf\n", glfwGetTime());
        scene = new Scene(getLoader());
        printf("MainApplication::init - after  new Scene: %lf\n", glfwGetTime());



        auto screen = Screen(WindowManager::width, WindowManager::height, getLoader());
        printf("MainApplication::init - after  auto screen = Screen: %lf\n", glfwGetTime());
        PointerPointLight sun = createPointLight(Vector3f(100000, 100000, -100000), Vector3f(1.3f, 1.3f, 1.3f), Vector3f(1.0f, 0.0f, 0.0f));
        PointerPointLight light = createPointLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
        PointerPointLight light1 = createPointLight(Vector3f(200, 10, 200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

        scene -> addLight(sun);
        renderer -> setSun(sun);

//        renderer -> setPostFx(true);

        setView(new FpsView(renderer -> getActualCamera(), true));
        printf("MainApplication::init - end: %lf\n", glfwGetTime());
    };
    void update(float delta) override {
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = eq(delta, 1.0f) ? 0.2f : 1.0f;
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
            glfwSetWindowShouldClose(WindowManager::window, 1);
        }
    };
    void onSecondElapse(int fps) override{
//        printf("FPS: %d\n", fps);
    }
    void render(void) override {
        renderer -> renderScene(*scene);
//        renderer -> renderSceneDeferred(*scene);
    };
    void cleanUp(void) override {
        localCleanUp();
        printf("maže sa renderer v main application\n");
        renderer -> cleanUp();
        delete renderer;

        scene -> cleanUp();
        delete scene;
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
