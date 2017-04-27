//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINAPPLICATION_H
#define GRAPHICSPROJECT_MAINAPPLICATION_H


#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include "BasicApplication.h"

#include <src/rendering/material/TextureManager.h>
#include <src/components/terrain/TerrainManager.h>
#include <src/components/voxel/World.h>

class MainApplication : public BasicApplication{
private:
    float time                          = 0;
    PointerEntity barrel                = nullptr;
    PointerEntity teaEntity             = nullptr;
    PointerMaterialedModel ball         = nullptr;
    PointerTexture2D particleTexture    = nullptr;
public:
    inline Renderer * getMainRenderer(void){
        return (Renderer *)getRenderer();
    }
    inline void loadContent() override {
        DEBUG("načítavam content");
        auto skyTexture = TextureManager::createCubeTexture("sky");
        getScene()->setSky(skyTexture);

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

        TerrainManager terrainManager = TerrainManager(getLoader(), 100, (Scene *)getScene());
        terrainManager.generateTerrain(diffuse, 128, 5, 40, 0, 0);
//        getRenderer()->getMaster()->getVoxel()->setWorld(new World(getScene(), rawModel));

//        for(int i=0 ; i<3000 ; i++){
//            float x = (float)random(0, 100);
//            float y = (float)random(0, 100);
//            PRINT("x: " << x << ", z: " << y);
//            getScene() -> addEntity(createEntity(model, Vector3f(x, terrainManager.getHeight(x, y) , y), Vector3f(0, 0, 0), Vector3f(0.01, 0.01, 0.01)));
//        }
        PRINT(terrainManager.getHeight(0, 0) << ", " << terrainManager.getHeight(10, 0) << ", " << terrainManager.getHeight(0, 10) << ", " << terrainManager.getHeight(10, 10));
        PRINT(terrainManager.getHeight(0, 0) << ", " << terrainManager.getHeight(20, 0) << ", " << terrainManager.getHeight(0, 20) << ", " << terrainManager.getHeight(20, 20));
        PRINT(terrainManager.getHeight(0, 0) << ", " << terrainManager.getHeight(30, 0) << ", " << terrainManager.getHeight(0, 30) << ", " << terrainManager.getHeight(30, 30));

        getRenderer()->getMaster()->getWater()->addWater(-50, -50, 1.5f);
        /*
        terrainManager.generateTerrain(diffuse, 128, 5, 40,  0,  0);
        terrainManager.generateTerrain(diffuse, 128, 5, 40, -1,  0);
        terrainManager.generateTerrain(diffuse, 128, 5, 40,  0, -1);
        */
    }

    inline void init(BasicGtkGui * gui) {

        DEBUG("MainApplication::init - start: " << glfwGetTime());
//        gui.init();

        //renderer = new Renderer(getLoader(), WindowManager::width, WindowManager::height);
        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        if(gui){
            gui -> setWater(new GtkWater(getMainRenderer() -> getMaster() -> getWater()));
            gui -> setPostFx(new GtkPostFx(getMainRenderer() -> getMaster() -> getPostFx()));
            gui -> setRenderer(new GtkRenderer(getMainRenderer()));
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
            entity->setVelocity(getRenderer() -> getActualCamera() -> getForward());
            getScene()->addObject(entity);
        }
    }

    inline void onSecondElapse(int fps) override{
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
        TextureManager::cleanUp();
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
