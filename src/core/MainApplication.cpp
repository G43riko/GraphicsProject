//
// Created by gabriel on 14.1.2017.
//

#include "MainApplication.h"

void MainApplication::init(BasicGtkGui * gui) {

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

void MainApplication::update(float delta) {
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
        PointerGameObject entity = PointerGameObject(new GameObject(createEntity(ball, getRenderer() -> getActualCamera() -> getPosition(), Vector3f(), Vector3f(1))));
        entity->setVelocity(getRenderer() -> getActualCamera() -> getForward());
        getScene()->addObject(entity);
    }
}