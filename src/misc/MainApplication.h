//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_MAINAPPLICATION_H
#define GRAPHICSPROJECT_MAINAPPLICATION_H

#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include "src/core/BasicApplication.h"

#include <src/rendering/model/GObjects.h>
#include <src/rendering/model/models/Cylinder.h>
#include <src/rendering/model/models/Box.h>
#include <src/rendering/material/TextureManager.h>
#include <src/components/terrain/TerrainManager.h>
#include <src/components/text/TextMaster.h>
#include <src/components/voxel_old/World_old.h>
#include <src/utils/resources/OBJParralelLoader.h>

class MainApplication : public BasicApplication{
    float time                          = 0;
    PointerEntity barrel                = nullptr;
    PointerEntity teaEntity             = nullptr;
    PointerMaterialedModel ball         = nullptr;

    TextMaster *texts;
    PointerTexture2D particleTexture    = nullptr;
public:
    inline void loadContent(void) override {
        DEBUG("načítavam content");
        const PointerCubeTexture skyTexture = TextureManager::instance.createCubeTexture("sky");
        getScene()->setSky(skyTexture);

        OBJLoader objLoader = OBJLoader({"box", "plane", "sphere", "tea"});
        objLoader.startLoadAsynch();
        //////////////////////////////////////////////////////////Začiatok načítavanie OBJ súborov

        particleTexture = TextureManager::instance.createTexture2D("res/textures/particle_1.png");
        const PointerTexture2D diffuse = TextureManager::instance.createTexture2D("res/textures/texture.png");
        const PointerTexture2D normal = TextureManager::instance.createTexture2D("res/textures/textureNormal.png");
        const PointerTexture2D green = TextureManager::instance.createTexture2D("res/textures/green.png");


        getScene() -> setTerrainManager(new TerrainManager(getLoader(), 100, getScene()));
        getScene() -> getTerrainManager() -> generateTerrain(diffuse, 128, 5, 40, 1, 0);


        const PointerMaterial teaMaterial = Material::create(green);
        const PointerMaterial material = Material::create(diffuse, normal);


        const PointerRawModel line = getLoader().loadToVao(GObjects::createLine({Vector3f(),
                                                                                 {0, 5, 0},
                                                                                 {0, 5, 5,},
                                                                                 {5, 5, 5}}), GL_LINE_STRIP);

        //////////////////////////////////////////////////////////Koniec načítavanie OBJ súborov
        objLoader.waitLoadAsynch();

        const PointerRawModel rawModel = objLoader.getRawModel(getLoader(), "box");
        const PointerRawModel tea = objLoader.getRawModel(getLoader(), "tea");
        const PointerRawModel plane = objLoader.getRawModel(getLoader(), "plane");
        const PointerRawModel sphere = objLoader.getRawModel(getLoader(), "sphere");
        objLoader.cleanUp();

        ((Scene*)getScene())->loadParticleTexture(particleTexture, 4, 4);
        getScene() -> createParticleSystem(particleTexture, 1, 5, 0, 100);

        ball = MaterialedModel::create(sphere, material);
        const PointerMaterialedModel teaModel = MaterialedModel::create(tea, teaMaterial);
        const PointerMaterialedModel model = MaterialedModel::create(rawModel, material);
        const PointerMaterialedModel floor = MaterialedModel::create(plane, Material::create(diffuse, normal));
        const PointerMaterialedModel barrelModel = MaterialedModel::create("barrel", getLoader());


        getScene() -> addEntity(Entity::create(MaterialedModel::create(line, nullptr),
                                               Vector3f(0, 0, 0),
                                               Vector3f(0, 0, 0),
                                               Vector3f(1, 2, 1)));

        Cylinder cylinder(1, 1, 3);

        getRenderer().getMaster().getWater() -> addWater(-50, -50, 1.5f);

        getScene() -> addEntity(Entity::create(MaterialedModel::create(getLoader().loadToVao(cylinder.getMesh()),
                                                                       material),
                                               Vector3f(0, 10, 0),
                                               Vector3f(0, 0, 0),
                                               Vector3f(1, 1, 1)));
        Box boxMod(3, 3, 3);
        getScene() -> addEntity(Entity::create(MaterialedModel::create(getLoader().loadToVao(boxMod.getMesh()),
                                                                       material),
                                               Vector3f(0, 10, -5),
                                               Vector3f(0, 0, 0),
                                               Vector3f(1, 1, 1)));

        teaEntity = Entity::create(teaModel, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
        teaMaterial -> setEnvironmentalMap(skyTexture);

        getScene() -> addEntity(teaEntity);
        barrel = Entity::create(barrelModel,
                                Vector3f(0, 4, 0),
                                Vector3f(0.0f, 0.0f, (float)(M_PI / 2)),
                                Vector3f(0.1f, 1.0f, 0.1f));
        getScene() -> addEntity(barrel);

        getScene() -> addEntity(Entity::create(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(Entity::create(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(Entity::create(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(Entity::create(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(Entity::create(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

        getScene() -> addEntity(Entity::create(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
        getScene() -> addEntity(Entity::create(floor, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(10, 1, 10)));

        texts = new TextMaster(getRenderer().getActualCamera());

    }

    inline void init(BasicGtkGui * gui) {
        DEBUG("MainApplication::init - start: " << glfwGetTime());
//        gui.init();

        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        if(gui){
            gui -> setWater(new GtkWater(getRenderer().getMaster().getWater()));
            gui -> setPostFx(new GtkPostFx(getRenderer().getMaster().getPostFx()));
            gui -> setRenderer(new GtkRenderer(((Renderer*)&getRenderer())));
        }

        DEBUG("MainApplication::init - after  new Renderer: " << glfwGetTime());
        setScene(new Scene(getLoader()));
        DEBUG("MainApplication::init - after  new Scene: " << glfwGetTime());

        DEBUG("MainApplication::init - after  auto screen = Screen: " << glfwGetTime());
        PointerPointLight sun = PointLight::create(Vector3f(100000, 100000, -100000),
                                                   Vector3f(1.3f, 1.3f, 1.3f),
                                                   Vector3f(1.0f, 0.0f, 0.0f));

        PointerPointLight light = PointLight::create(Vector3f(0, 0, 0),
                                                     Vector3f(1, 1, 1),
                                                     Vector3f(1.0f, 0.01f, 0.002f));

        PointerPointLight light1 = PointLight::create(Vector3f(200, 10, 200),
                                                      Vector3f(0.5f, 0.0f, 0.8f),
                                                      Vector3f(1.0f, 0.1f, 0.02f));

        getScene() -> addLight(sun);
        getRenderer().setLight(sun);

        setView(new FpsView(getRenderer().getActualCamera(), true));
        DEBUG("MainApplication::init - end: " << glfwGetTime());
    }

    inline void update(float delta) {
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = EQ(delta, 1.0f) ? 0.2f : 1.0f;
        }
        barrel -> getTransform() -> getRotation().rotate(Vector3f(0.00f, 0.05f, 0.0f) * delta);
        teaEntity -> getTransform() -> getRotation().rotate(Vector3f(0.0f, 0.005f, 0.0f) * delta);


        time += 0.02f * delta;

        updateApp(delta);

        if(Input::isKeyDown(GLFW_KEY_F)){
            for(int i=0 ; i<10 ; i++){
                ((Scene*)getScene()) -> createParticle(particleTexture,
                                                       Vector3f(0.0f, 2.0f, -2.0f),
                                                       Vector3f(grandom(-0.02, 0.02),
                                                                grandom(0.01, 0.1),
                                                                grandom(-0.02, 0.02)),
                                                       0,
                                                       100,
                                                       0,
                                                       1);
            }
        }

        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            //glfwSetWindowShouldClose(WindowManager::window, 1);
            stop();
        }

        if(Input::getMouseDown(0)){
            PointerGameObject entity = GameObject::create(Entity::create(ball,
                                                                         getRenderer().getActualCamera() -> getPosition(),
                                                                         Vector3f(),
                                                                         Vector3f(1, 1, 1)));
            entity->setGravityEffect(0.01f);
            entity->setVelocity(getRenderer().getActualCamera() -> getForward());
            getScene()->addObject(entity);
        }
    }

    inline void render(void) override {
        getRenderer().renderScene(((Scene *)getScene()));
        texts -> renderTexts();
//        getRenderer().renderSceneDeferred(((Scene *)getScene()));
    };
    inline void cleanUp(void) override {
        DEBUG("maže sa renderer v main application");
        getLoader().cleanUp();
        TextureManager::instance.cleanUp();
    };
};


#endif //GRAPHICSPROJECT_MAINAPPLICATION_H
