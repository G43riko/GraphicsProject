//
// Created by gabriel on 18.4.2017.
//

#ifndef GAMEENGINE_VOXELAPPLICATION_H
#define GAMEENGINE_VOXELAPPLICATION_H


#include <src/core/BasicApplication.h>
#include <src/components/movement/FpsView.h>
#include <src/components/voxel/chunks/ChunkBuilder.h>

class VoxelApplication : public BasicApplication{

    PointerMaterialedModel ball = nullptr;
    PointerEntity ballEntity = nullptr;
    PointerGameObject ballObject = nullptr;
    PointerSpotLight spotLight = nullptr;
    void loadContent() override {
        DEBUG("načítavam content");
        auto skyTexture = TextureManager::instance.createCubeTexture("sky");
        PRINT("PLANEEEEE<<<<<<<<<<<<<<<<<<<<\n\n");
        auto plane = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/plane.obj"));
        auto sphere = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj"));
        auto box = getLoader().loadToVao(ContentLoader::loadOBJ("res/models/box.obj"));
        auto diffuse = TextureManager::instance.createTexture2D("res/textures/texture.png");
        auto normal = TextureManager::instance.createTexture2D("res/textures/textureNormal.png");
        auto cursor = TextureManager::instance.createTexture2D("res/textures/aim_cursor.png");
        float size = 50;

        getRenderer().addTexture(GuiTexture(cursor -> getTextureID(),
                                               Vector2f(),
                                               Vector2f(size / (float)WindowManager::width,
                                                        size / (float)WindowManager::height)));

        auto material = Material::create(diffuse, normal);
        ball = MaterialedModel::create(sphere, material);
        getScene()->setSky(skyTexture);

        getRenderer().getMaster().getVoxel()->setWorld(new World_old(getScene(), plane, box));

        PointerPointLight sun = PointLight::create(Vector3f(100000, 100000, -100000), Vector3f(0.6f, 0.6f, 0.6f));
        getRenderer().getMaster().getVoxel()->setTexture(normal);
//        getScene() -> addLight(PointLight::create(Vector3f(-6.0f, 0.0f, -6.0f), Vector3f(1, 0, 1)));
//        getScene() -> addLight(sun);
        getRenderer().setLight(sun);
        ballEntity = Entity::create(ball, sun->getPosition(), Vector3f(0, 0, 0), Vector3f(0.1, 0.1, 0.1));
        getScene() -> addEntity(ballEntity);

        Loader l = getLoader();
        int num = 8;
        LOOP(num, i){
            LOOP(num, j){
                getRenderer().getMaster().getVoxel()->generateChunk({i, j}, &l);
            }
        }

        spotLight = SpotLight::create(getRenderer().getActualCamera()->getPosition(), {1, 1, 1}, {1.0f, 0.1f, 0.0002f}, {0, 0, 1}, COSF(TO_RADIANS(3.5f)), COSF(TO_RADIANS(14.5f)));
        getScene() -> addLight(spotLight);


        getRenderer().setSun(DirectionalLight::create({1, 1, 1}, getRenderer().getActualCamera()->getForward()));

    }
    void init(BasicGtkGui * gui) override{
        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        setScene(new Scene(getLoader()));
        setView(new FpsView(getRenderer().getActualCamera(), true));



        DEBUG("MainApplication::init - end: " << glfwGetTime());
    };
    void update(float delta) override{
        if(Input::getKeyDown(GLFW_KEY_X)){
            delta = EQ(delta, 1.0f) ? 0.2f : 1.0f;
        }

        spotLight->setPosition(getRenderer().getActualCamera() -> getPosition());
        spotLight->setDirection(getRenderer().getActualCamera() -> getForward());

        getRenderer().prepareRenderer(0, 0, 0, 1);
        getRenderer().init3D();
        getRenderer().input();
        getRenderer().update(delta);
        getScene() -> update(delta);
        getView().update(delta);


        if(Input::isKeyDown(GLFW_KEY_ESCAPE)){
            //glfwSetWindowShouldClose(WindowManager::window, 1);
            stop();
        }
        if(IS_NULL(ballObject)){
            if(Input::getMouseDown(0)){
                getRenderer().getSun() -> setDirection(getRenderer().getActualCamera()->getForward());


//                PointerPointLight sun = getRenderer().getLight();
//                Vector3f newPos = getRenderer().getActualCamera() -> getPosition() + getRenderer().getActualCamera() -> getForward() * 5;
//                ballEntity -> getTransform() -> setPosition(newPos);
//                sun->setPosition(newPos.x, newPos.y, newPos.z);



//                ballObject = GameObject::create(Entity::create(ball, getRenderer().getActualCamera() -> getPosition(), Vector3f(), Vector3f(0.1, 0.1, 0.1)));
//                ballObject->setVelocity(getRenderer().getActualCamera() -> getForward());
//                getScene()->addObject(ballObject);
            }
        }
        else{
            Vector3f pos = ballObject->getObject()->getTransform()->getPosition();
            Block * block = getRenderer().getMaster().getVoxel()->getWorld()->getBlockOn(pos.getXi(), pos.getYi(), pos.getZi());
            if(IS_NOT_NULL(block)){
                Chunk_old * chunk = block->getParent();
                if(IS_NOT_NULL(chunk)){
                    chunk->removeBlock(block->getPosition());
                    getScene()->removeObject(ballObject);
                    ballObject = nullptr;
                }
            }
        }
    };

    void onSecondElapse(const int fps) override{
//        printf("FPS: %d\n", fps);
        PRINT("FPS: " << fps);
    };

    void render(void) override {
        getRenderer().renderScene(((Scene *)getScene()));


//        getRenderer().renderSceneDeferred(((Scene *)getScene()));
    };

    void cleanUp(void) override {
        DEBUG("maže sa renderer v voxel_old application");
        TextureManager::instance.cleanUp();
    };
};


#endif //GAMEENGINE_VOXELAPPLICATION_H
