

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
#include <src/entities/Terrain.h>
#include <src/components/FpsView.h>
#include <src/components/TopView.h>
#include <src/game/Ball.h>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"
#include <time.h>
#include <src/game/Environment.h>
#include <src/game/Arrow.h>

int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);

    WindowManager::init(800, 600, "Okno", false);
    Input::init(WindowManager::window, WindowManager::width, WindowManager::height);

    Loader loader = Loader();
    Renderer renderer = Renderer(loader, WindowManager::width, WindowManager::height);

    Scene scene = Scene(loader, ContentLoader::loadCubeTexture("sky"));
    Environment environment = Environment();

    //auto barel = ContentLoader::loadTexturePNG("res/textures/barrel.png");
    //auto barel = ContentLoader::loadTexturePNG("res/textures/barrel.png");
    auto diffuse = ContentLoader::loadTexturePNG("res/textures/texture.png");
    auto ballDiffuse = ContentLoader::loadTexturePNG("res/textures/ball.png");
    auto normal = ContentLoader::loadTexturePNG("res/textures/textureNormal.png");
    auto ballNormal = ContentLoader::loadTexturePNG("res/textures/barrelNormal.png");
    auto axeDiffuse = ContentLoader::loadTexturePNG("res/textures/crossbow.png");
    auto axeNormal = ContentLoader::loadTexturePNG("res/textures/axeNormal.png");

    auto rawModel = loader.loadToVao(ContentLoader::loadOBJ("res/models/box.obj"));
    auto plane = loader.loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
    auto crossbow = loader.loadToVao(ContentLoader::loadOBJ("res/models/crossbow.obj"));
    auto sphere = loader.loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj"));
    auto boar = loader.loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj"));
    //ContentLoader::loadOBJ("res/models/axe.obj") ->show();


    auto model = createMaterialedModel(rawModel, createMaterial(diffuse, normal));
    auto lightModel = createMaterialedModel(sphere, createMaterial(ballDiffuse, normal));
    auto floor = createMaterialedModel(plane, createMaterial(diffuse, normal));
    auto boarModel = createMaterialedModel(boar, createMaterial(diffuse, normal));
    auto axeModel = createMaterialedModel(crossbow, createMaterial(axeDiffuse, axeNormal));
    auto bulletModel = createMaterialedModel(sphere, createMaterial(ContentLoader::loadTextureColor(Vector3f(255, 255, 0)), axeNormal));
    auto barrelModel = createMaterialedModel("barrel", loader);

    auto entity = createEntity(model, Vector3f(0, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    float axeSize = 0.008;
    auto axeEntity = createEntity(axeModel, Vector3f(1, 0, 0), Vector3f(M_PI_2, 0.0, M_PI_2), Vector3f(axeSize));
    auto barrel = createEntity(barrelModel, Vector3f(0, 0, 0), Vector3f(0.0f, 0.0f, (float)(M_PI / 2)), Vector3f(0.1f, 1.0f, 0.1f));
    scene.addEntity(barrel);
    scene.addEntity(axeEntity);

    scene.addEntity(createEntity(model, Vector3f(5, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(0, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(5, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 0, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

    PointerEntity player = createEntity(boarModel, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    axeEntity->getTransform()->setParent(player->getTransform(), true, false, false);

    Ball ball = Ball(player);
    scene.addEntity(player);
    for(int i=0 ; i<100 ; i++)
        scene.addObject(PointerGameObject(new Ball(createEntity(lightModel, Vector3f(rand() % 100 - 50, 0, rand() % 100 - 50), Vector3f(0.0f), Vector3f(1.0f)))));


    scene.addEntity(createEntity(model, Vector3f(5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(0, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
    scene.addEntity(createEntity(model, Vector3f(-5, 3, -15), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));

    auto floorEntity = createEntity(floor, Vector3f(0, -1, 0), Vector3f(), Vector3f(10, 1, 10));
    scene.addEntity(floorEntity);
//    Terrain t = Terrain(1, 1, loader, diffuse, 10);
//    scene.addEntity(createEntity(t.getModel(), Vector3f(0, -1, 0), Vector3f(0.0f), Vector3f(1.0f)));

    auto screen = Screen(WindowManager::width, WindowManager::height, loader);
    PointerLight light = createLight(Vector3f(0, 0, 0), Vector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
    PointerLight light1 = createLight(Vector3f(200, 10,  200), Vector3f(0.5f, 0.0f, 0.8f), Vector3f(1.0f, 0.1f, 0.02f));

    auto lightEntity = createEntity(lightModel, Vector3f(0, 0, 0), Vector3f(0, 0, 0), Vector3f(1, 1, 1));
    scene.addEntity(lightEntity);
    scene.addLight(light);
    scene.addLight(light1);
//    scene.addEntity(entity);
    int objects = (int)scene.getEntities().size();
    renderer.setPostFx(true);

    //renderer.addTexture(GuiTexture(diffuse -> getTextureID(), Vector2f(0.5f, 0.5f), Vector2f(0.25f, 0.25f)));
//    BasicView * view = new FpsView(renderer.getActualCamera(), false, &ball);
    BasicView * view = new TopView(renderer.getActualCamera(), 30, &ball);
    float time = 0;

    float oldPitch = renderer.getActualCamera() -> pitch;
    double currentTime = glfwGetTime();
    int fps = 0;
    while (!WindowManager::isCloseRequest()) {
        axeEntity ->getTransform() -> getPosition()-> x = cos(renderer.getActualCamera()->yaw);
        axeEntity ->getTransform() -> getPosition()-> z = sin(renderer.getActualCamera()->yaw);
        axeEntity ->getTransform() -> setRotation(Quaternion(Vector3f(0, 1, 0), renderer.getActualCamera()->yaw));
        barrel -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.05f, 0.0f));
        fps++;
        if(glfwGetTime() - currentTime > 1.0){
            printf("FPS: %d, chytil si %d/%d lôpt\n", fps, objects - (int)scene.getEntities().size(), 100);
            fps = 0;
            currentTime = glfwGetTime();
        }
        if(view -> name == "fpsView"){
            //ball.getObject()->setAlive(false);
            *axeEntity->getTransform()->getRotation() *= Quaternion(axeEntity->getTransform()->getRotation()->getRight(), oldPitch - renderer.getActualCamera() -> pitch);
            oldPitch = renderer.getActualCamera() -> pitch;
        }
        ball.update(1);
        renderer.prepareRenderer(0, 0, 0, 1);
        time += 0.02f;
        renderer.init3D();
        light1 -> setPosition(static_cast<float>(-sin(time) * 20) , 0, static_cast<float>(-cos(time) * 20 - 20));
        light -> setPosition(static_cast<float>(sin(time) * 20) , 0, static_cast<float>(cos(time) * 20 - 20));
//        entity -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.005f, 0.00f));

        scene.update(1);
        ball.getObject()->setAlive(true);
        lightEntity -> getTransform() ->setPosition(light -> getPosition());
        renderer.input();
        view -> input();
        renderer.renderScene(scene);
        if(Input::getKeyDown(GLFW_KEY_SPACE) || Input::getMouseDown(0)){
            PointerEntity e = createEntity(barrelModel, player->getTransform()->getPosition() + *axeEntity ->getTransform() -> getPosition(),
                                           Vector3f(),
                                           Vector3f(0.01f, 0.4f, 0.01f));
            e ->getTransform()->setRotation(*axeEntity->getTransform() ->getRotation() * Quaternion(Vector3f(cos(renderer.getActualCamera()->yaw),
                                                                                                             0.0,
                                                                                                             sin(renderer.getActualCamera()->yaw)), M_PI_2));

            Vector3f vel = Vector3f(sin(renderer.getActualCamera()->yaw), 0.1, -cos(renderer.getActualCamera()->yaw));
            if(view -> name == "fpsView")
                vel.y = -renderer.getActualCamera() -> pitch + 0.1f;
            scene.addObject(PointerGameObject(new Arrow(e, vel, &environment)));
        }


        if(Input::isKeyDown(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(WindowManager::window, 1);
        Input::update();
        WindowManager::update();
    }
    renderer.cleanUp();
    scene.cleanUp();
    screen.cleanUp();
    loader.cleanUp();
    WindowManager::close();
    std::cout << "vectors: " << Vector3f::count << std::endl;
    return 0;
}