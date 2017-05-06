//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINAPPLICATION_H
#define GRAPHICSPROJECT_MAINAPPLICATION_H

#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include "BasicApplication.h"

#include <src/rendering/model/GObjects.h>
#include <src/rendering/material/TextureManager.h>
#include <src/components/terrain/TerrainManager.h>
#include <src/components/voxel/World.h>
#include <src/utils/OBJLoader.h>
#include <map>

class MainApplication : public BasicApplication{
private:
    float time                          = 0;
    PointerEntity barrel                = nullptr;
    PointerEntity teaEntity             = nullptr;
    PointerMaterialedModel ball         = nullptr;
    PointerTexture2D particleTexture    = nullptr;
public:
    inline void loadContent() override {
        DEBUG("načítavam content");
        auto skyTexture = TextureManager::instance.createCubeTexture("sky");
        getScene()->setSky(skyTexture);

        OBJLoader objLoader = OBJLoader({"box", "plane", "sphere", "tea"});
        objLoader.startLoadAsynch();
        //////////////////////////////////////////////////////////Začiatok načítavanie OBJ súborov

        particleTexture = TextureManager::instance.createTexture2D("res/textures/particle_1.png");
        auto diffuse = TextureManager::instance.createTexture2D("res/textures/texture.png");
        auto normal = TextureManager::instance.createTexture2D("res/textures/textureNormal.png");
        auto green = TextureManager::instance.createTexture2D("res/textures/green.png");


        getScene() -> setTerrainManager(new TerrainManager(getLoader(), 100, getScene()));
        getScene() -> getTerrainManager() -> generateTerrain(diffuse, 128, 5, 40, 1, 0);

        auto teaMaterial = createMaterial(green);
        auto material = createMaterial(diffuse, normal);


        auto line = getLoader().loadToVao(GObjects::createLine({Vector3f(), {0, 5, 0}, {0, 5, 5,}, {5, 5, 5}}), GL_LINE_STRIP);

        //////////////////////////////////////////////////////////Koniec načítavanie OBJ súborov
        objLoader.waitLoadAsynch();

        auto rawModel = objLoader.getRawModel(getLoader(), "box");
        auto tea = objLoader.getRawModel(getLoader(), "tea");
        auto plane = objLoader.getRawModel(getLoader(), "plane");
        auto sphere = objLoader.getRawModel(getLoader(), "sphere");
        objLoader.cleanUp();

        ball = createMaterialedModel(sphere, material);
        auto teaModel = createMaterialedModel(tea, teaMaterial);
        auto model = createMaterialedModel(rawModel, material);
        auto floor = createMaterialedModel(plane, createMaterial(diffuse, normal));
        auto barrelModel = createMaterialedModel("barrel", getLoader());


        getScene() -> addEntity(createEntity(createMaterialedModel(line, teaMaterial), Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(1, 2, 1)));

        teaEntity = createEntity(teaModel, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        teaMaterial -> setEnvironmentalMap(skyTexture);

        getScene() -> addEntity(teaEntity);
        barrel = createEntity(barrelModel, Vector3f(0, 4, 0), Vector3f(0.0f, 0.0f, (float)(M_PI / 2)), Vector3f(0.1f, 1.0f, 0.1f));
        getScene() -> addEntity(barrel);

        getScene() -> addEntity(createEntity(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(createEntity(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(createEntity(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(createEntity(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

        getScene() -> addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(createEntity(floor, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(10, 1, 10)));

    }

    inline void init(BasicGtkGui * gui) {
        DEBUG("MainApplication::init - start: " << glfwGetTime());
//        gui.init();

        //renderer = new Renderer(getLoader(), WindowManager::width, WindowManager::height);
        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        if(gui){
            gui -> setWater(new GtkWater(getRenderer() -> getMaster() -> getWater()));
            gui -> setPostFx(new GtkPostFx(getRenderer() -> getMaster() -> getPostFx()));
            gui -> setRenderer(new GtkRenderer((Renderer *)getRenderer()));
        }

        DEBUG("MainApplication::init - after  new Renderer: " << glfwGetTime());
        setScene(new Scene(getLoader()));
        DEBUG("MainApplication::init - after  new Scene: " << glfwGetTime());



//    auto screen = Screen(WindowManager::width, WindowManager::height, getLoader());
        DEBUG("MainApplication::init - after  auto screen = Screen: " << glfwGetTime());
        PointerPointLight sun = createPointLight(Vector3f(100000, 100000, -100000), Vector3f(1.3f, 1.3f, 1.3f), Vector3f(1.0f, 0.0f, 0.0f));
        PointerPointLight light = createPointLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
        PointerPointLight light1 = createPointLight(Vector3f(200, 10, 200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

        getScene() -> addLight(sun);
        getRenderer() -> setSun(sun);

//        renderer -> setPostFx(true);

        setView(new FpsView(getRenderer() -> getActualCamera(), true));
        DEBUG("MainApplication::init - end: " << glfwGetTime());
    }

    inline void update(float delta) {
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = EQ(delta, 1.0f) ? 0.2f : 1.0f;
        }
        barrel -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.05f, 0.0f) * delta);
        teaEntity -> getTransform() -> getRotation() -> rotate(Vector3f(0.0f, 0.005f, 0.0f) * delta);

        getRenderer() -> prepareRenderer(0, 0, 0, 1);
        time += 0.02f * delta;
        getRenderer() -> init3D();
        getScene() -> update(delta);
        getView().update(delta);
        getRenderer() -> input();
        getRenderer() -> update(delta);
        if(Input::isKeyDown(GLFW_KEY_F)){
            ((Scene*)getScene()) -> createParticle(particleTexture, Vector3f(0.0f, 2.0f, -2.0f), Vector3f(random(-0.02, 0.02), random(0.01, 0.1), random(-0.02, 0.02)), 0, 100, 0, 1);
        }

        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            //glfwSetWindowShouldClose(WindowManager::window, 1);
            stop();
        }

        if(Input::getMouseDown(0)){
            PointerGameObject entity = PointerGameObject(new GameObject(createEntity(ball, getRenderer() -> getActualCamera() -> getPosition(), Vector3f(), Vector3f(1, 1, 1))));
            entity->setGravityEffect(0.01f);
            entity->setVelocity(getRenderer() -> getActualCamera() -> getForward());
            getScene()->addObject(entity);
        }
    }

    inline void onSecondElapse(const int fps) override{
//        printf("FPS: %d\n", fps);
        PRINT("FPS: " << fps);
    };
    inline void render(void) override {
        getRenderer() -> renderScene(((Scene *)getScene()));

//        renderer -> renderSceneDeferred(((Scene *)getScene()));
    };
    inline void cleanUp(void) override {
        DEBUG("maže sa renderer v main application");
        getLoader().cleanUp();
        TextureManager::instance.cleanUp();
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
