//
// Created by gabriel on 18.4.2017.
//

#ifndef GAMEENGINE_VOXELAPPLICATION_H
#define GAMEENGINE_VOXELAPPLICATION_H


#include <src/utils/Performance.h>
#include <src/core/BasicApplication.h>
#include <src/components/movement/FpsView.h>

class VoxelApplication : public BasicApplication{
    PointerMaterialedModel ball = nullptr;
    void loadContent() override {
        DEBUG("načítavam content");
        auto skyTexture = TextureManager::createCubeTexture("sky");
        auto plane = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
        auto sphere = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj"));
        auto diffuse = TextureManager::createTexture2D("res/textures/texture.png");
        auto normal = TextureManager::createTexture2D("res/textures/textureNormal.png");
        auto material = createMaterial(diffuse, normal);
        ball = createMaterialedModel(sphere, material);
        getScene()->setSky(skyTexture);

        getRenderer()->getMaster()->getVoxel()->setWorld(new World(getScene(), plane));
    }
    void init(BasicGtkGui * gui) override{

        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        setScene(new Scene(getLoader()));


        PointerPointLight sun = createPointLight(Vector3f(100000, 100000, -100000), Vector3f(1.3f, 1.3f, 1.3f), Vector3f(1.0f, 0.0f, 0.0f));

        getScene() -> addLight(sun);
        getRenderer() -> setSun(sun);


        setView(new FpsView(getRenderer() -> getActualCamera(), true));
        DEBUG("MainApplication::init - end: " << glfwGetTime());
    };
    void update(float delta) override{
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = EQ(delta, 1.0f) ? 0.2f : 1.0f;
        }
        getRenderer() -> prepareRenderer(0, 0, 0, 1);
        getRenderer() -> init3D();
        getRenderer() -> input();
        getRenderer() -> update(delta);

        getScene() -> update(delta);
        getView().update(delta);

        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            //glfwSetWindowShouldClose(WindowManager::window, 1);
            stop();
        }

        if(Input::getMouseDown(0)){
            PointerGameObject entity = PointerGameObject(new GameObject(createEntity(ball, getRenderer() -> getActualCamera() -> getPosition(), Vector3f(), Vector3f(1))));
            entity->setVelocity(getRenderer() -> getActualCamera() -> getForward());
            getScene()->addObject(entity);
        }
    };

    void onSecondElapse(int fps) override{
//        printf("FPS: %d\n", fps);
        PRINT("FPS: " << fps);
    };

    void render(void) override {
        getRenderer() -> renderScene(((Scene *)getScene()));
    };

    void cleanUp(void) override {
        DEBUG("maže sa renderer v voxel application");
        TextureManager::cleanUp();
    };
};


#endif //GAMEENGINE_VOXELAPPLICATION_H
