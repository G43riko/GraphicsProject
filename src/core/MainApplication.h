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
    Renderer * getMainRenderer(void){
        return (Renderer *)getRenderer();
    }
    void loadContent() override {
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

        //renderer->getWaterMaster()->addWater(-50, -50, 1.5f);
        /*
        terrainManager.generateTerrain(diffuse, 128, 5, 40,  0,  0);
        terrainManager.generateTerrain(diffuse, 128, 5, 40, -1,  0);
        terrainManager.generateTerrain(diffuse, 128, 5, 40,  0, -1);
        */
    }

    void init(BasicGtkGui * gui) override;
    void update(float delta) override;

    void onSecondElapse(int fps) override{
//        printf("FPS: %d\n", fps);
        PRINT("FPS: " << fps);
    };
    void render(void) override {
        getRenderer() -> renderScene(((Scene *)getScene()));

//        renderer -> renderSceneDeferred(((Scene *)getScene()));
    };
    void cleanUp(void) override {
        DEBUG("maže sa renderer v main application");
        getLoader().cleanUp();
        TextureManager::cleanUp();
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
