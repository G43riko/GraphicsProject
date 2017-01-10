

#include "rendering/WindowManager.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include "src/components/postProccessing/Screen.cpp"
#include <memory>
#include "utils/Vectors.cpp"
#include <vector>
#include <src/components/postProccessing/Fbo.h>
#include <src/components/postProccessing/PostProccessing.h>
#include <src/components/water/WaterFrameBuffer.h>
#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include <src/components/movement/TopView.h>
#include <src/game/Ball.h>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"
#include <time.h>
#include <src/game/Environment.h>
#include <src/game/Arrow.h>
#include <src/components/shadows/ShadowMaster.h>
#include <src/components/terrain/HeightGenerator.h>

int main(void){
    WindowManager::init(800, 600, "Okno", true);
    Input::init(WindowManager::window, WindowManager::width, WindowManager::height);

    Loader loader = Loader();
    Renderer renderer = Renderer(loader, WindowManager::width, WindowManager::height);

    auto skyTexture = ContentLoader::loadCubeTexture("sky");
    Scene scene = Scene(loader, skyTexture);

    auto diffuse = ContentLoader::loadTexturePNG("res/textures/texture.png");
    auto normal = ContentLoader::loadTexturePNG("res/textures/textureNormal.png");
    auto rawModel = loader.loadToVao(ContentLoader::loadOBJ("res/models/box.obj"));
    auto plane = loader.loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
    auto green = ContentLoader::loadTexturePNG("res/textures/green.png");
    auto tea = loader.loadToVao(ContentLoader::loadOBJ("res/models/tea.obj"));

    auto teaMaterial = createMaterial(green);
    auto teaModel = createMaterialedModel(tea, teaMaterial);

    auto model = createMaterialedModel(rawModel, createMaterial(diffuse, normal));
    auto floor = createMaterialedModel(plane, createMaterial(diffuse, normal));
    auto barrelModel = createMaterialedModel("barrel", loader);


    auto teaEntity = createEntity(teaModel, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    teaMaterial -> setEnvironmentalMap(&skyTexture);
    scene.addEntity(teaEntity);
    auto barrel = createEntity(barrelModel, Vector3f(0, 1, 0), Vector3f(0.0f, 0.0f, (float)(M_PI / 2)), Vector3f(0.1f, 1.0f, 0.1f));
    scene.addEntity(barrel);

    scene.addEntity(createEntity(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

//    auto floorEntity = createEntity(floor, Vector3f(0, -1, 0), Vector3f(), Vector3f(10, 1, 10));
//    scene.addEntity(floorEntity);

    Terrain t = Terrain(loader, diffuse, 100, 128, 5, 40);
    scene.addEntity(createEntity(t.getModel(), Vector3f(-50, 1, -50), Vector3f(0.0f), Vector3f(1.0f)));

    auto screen = Screen(WindowManager::width, WindowManager::height, loader);
    PointerLight sun = createLight(Vector3f(10000000, 15000000, -10000000), Vector3f(1.3f, 1.3f, 1.3f), Vector3f(1.0f, 0.0f, 0.0f));
    PointerLight light = createLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
    PointerLight light1 = createLight(Vector3f(200, 10,  200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

    scene.addLight(sun);
//    scene.addLight(light);
//    scene.addLight(light1);


    renderer.setSun(sun);
    //renderer.setPostFx(true);


    //ShadowMaster shadows = ShadowMaster(renderer.getActualCamera());
    //renderer.addTexture(GuiTexture(shadowMaster.getShadowMap(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));
    //renderer.addTexture(GuiTexture(diffuse->getTextureID(), Vector2f(0.75f, 0.75f), Vector2f(0.25f, 0.25f)));


    BasicView * view = new FpsView(renderer.getActualCamera(), false);
//    BasicView * view = new TopView(renderer.getActualCamera(), 30, &ball);
    float time = 0;

    double currentTime = glfwGetTime();
    int fps = 0;
    float delta = 1;
    while (!WindowManager::isCloseRequest()) {
        fps++;
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = delta == 1.0f ? 0.2f : 1.0f;
        }
        if(glfwGetTime() - currentTime > 1.0){
            printf("FPS: %d\n", fps);
            fps = 0;
            currentTime = glfwGetTime();
        }

        barrel -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.05f, 0.0f) * delta);
        teaEntity -> getTransform() -> getRotation() -> rotate(Vector3f(0.0f, 0.005f, 0.0f) * delta);
//        if(Input::isKeyDown(GLFW_KEY_Y)){
//            printf("pridavam casticu\n");
//            scene.addParticle(Particle(Vector3f(), Vector3f(0.0f, 1.0f, 0.0f), 1, 2.0f, 0, 1));
//        }
        renderer.prepareRenderer(0, 0, 0, 1);
        time += 0.02f * delta;
        renderer.init3D();
        light1 -> setPosition(static_cast<float>(-sin(time) * 20) , 0, static_cast<float>(-cos(time) * 20 - 20));
        light -> setPosition(static_cast<float>(sin(time) * 20) , 0, static_cast<float>(cos(time) * 20 - 20));

        scene.update(delta);
        view -> update(delta);
        renderer.input();
        renderer.update(delta);
        renderer.renderScene(scene);
        ParticleTexture text = ParticleTexture(nullptr, 2, 3);
        if(Input::isKeyDown(GLFW_KEY_F)){
            scene.addParticle(Particle(nullptr, Vector3f(0.0f, 0.0f, -2.0f), Vector3f(0.0f, 0.1f, 0.0f), 0, 2000, 0, 1));
        }


        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(WindowManager::window, 1);
        }
        Input::update();
        WindowManager::update();
    }
    renderer.cleanUp();
    scene.cleanUp();
    screen.cleanUp();
    loader.cleanUp();
    WindowManager::close();
    std::cout << "vectors3f: " << Vector3f::count << std::endl;
    std::cout << "vectors4f: " << Vector4f::count << std::endl;
    std::cout << "Matrices4f: " << Matrix4f::counter << " / " << Matrix4f::minus << std::endl;
    return 0;
}