

#include "rendering/WindowManager.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include "postProccessing/Screen.cpp"
#include <memory>
#include "utils/Vectors.cpp"
#include <vector>
#include <src/postProccessing/Fbo.h>
#include <src/postProccessing/PostProccessing.h>
#include <src/water/WaterFrameBuffer.h>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"

int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);

    WindowManager::init(800, 600, "Okno", true);
    Input::init();

    Loader loader = Loader();
    Renderer renderer = Renderer(loader, WindowManager::width, WindowManager::height);
    PointerCubeTexture skyBox = ContentLoader::loadCubeTexture("sky");

    Scene scene = Scene(loader, skyBox);


    //auto barel = ContentLoader::loadTexturePNG("res/textures/barrel.png");
    //auto barel = ContentLoader::loadTexturePNG("res/textures/barrel.png");
    auto diffuse = ContentLoader::loadTexturePNG("res/textures/texture.png");
    auto normal = ContentLoader::loadTexturePNG("res/textures/textureNormal.png");
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/box.obj")));
    auto plane = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/plane.obj")));
    auto sphere = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj")));
    auto model = createMaterialedModel(rawModel, createMaterial(diffuse, normal));
    auto lightModel = createMaterialedModel(sphere, createMaterial(diffuse, normal));
    auto floor = createMaterialedModel(plane, createMaterial(diffuse, normal));
    auto entity = createEntity(model, Vector3f(0, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    auto barrel = createEntity(createMaterialedModel("barrel", loader), Vector3f(20, 5, -20), Vector3f(0.0f), Vector3f(1.0f));
    scene.addEntity(barrel);

    scene.addEntity(createEntity(model, Vector3f(5, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(0, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(5, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

    scene.addEntity(createEntity(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

    auto floorEntity = createEntity(floor, Vector3f(0, -1, 0), Vector3f(), Vector3f(10, 1, 10));
    scene.addEntity(floorEntity);

    auto screen = Screen(WindowManager::width, WindowManager::height, loader);
    PointerLight light = createLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
    PointerLight light1 = createLight(Vector3f(200, 10,  200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

    auto lightEntity = createEntity(lightModel, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    scene.addEntity(lightEntity);
    scene.addLight(light);
    scene.addLight(light1);
    scene.addEntity(entity);

    //renderer.setPostFx(true);

    renderer.addTexture(GuiTexture(diffuse -> getTextureID(), Vector2f(0.5f, 0.5f), Vector2f(0.25f, 0.25f)));


    float time = 0;
    while (!WindowManager::isCloseRequest()) {
        renderer.prepareRenderer(0, 0, 0, 1);
        time+= 0.02;
        renderer.init3D();
        light1 -> setPosition(-sin(time) * 20 , 0, -cos(time) * 20 - 20);
        light -> setPosition(sin(time) * 20 , 0, cos(time) * 20 - 20);
        entity -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.005f, 0.00f));

        lightEntity -> getTransform() ->setPosition( light -> getPosition());

        renderer.renderScene(scene);

        Input::update();
        WindowManager::update();
    }
    renderer.cleanUp();
    screen.cleanUp();
    loader.cleanUp();
    WindowManager::close();
    std::cout << "vectors: " << Vector3f::count << std::endl;
    return 0;
}