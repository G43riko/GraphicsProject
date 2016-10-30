

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
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"

int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //  exit(1);
    WindowManager::init(800, 600, "Okno", true);
    Input::init();

    Loader loader = Loader();
    Renderer renderer = Renderer();

    auto texture = createTexture2D(ContentLoader::loadTexture("res/textures/lena.rgb", 512, 512));
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/box.obj")));
    auto model = createMaterialedModel(rawModel, createMaterial(texture));
    auto entity = createEntity(model, createVector3f(0, 0, -5), createVector3f(0, 0, 0), createVector3f(1, 1, 1));

    std::vector<PointerLight> ligts{createLight(createVector3f(200, 10, -200), createVector3f(1, 0, 0)),
                                    createLight(createVector3f(200, 10,  200), createVector3f(0, 0, 1))};

    Screen screen = Screen(WindowManager::width, WindowManager::height, loader);
    while (!WindowManager::isCloseRequest()) {
        renderer.prepare(0, 0, 0, 1);
        renderer.init3D();
        entity -> getTransform() -> getRotation() -> x -= 0.03f;
        entity -> getTransform() -> getRotation() -> y -= 0.03f;
        entity -> getTransform() -> getRotation() -> z -= 0.03f;

        //renderer -> renderEntity(entity);

        screen.startRenderToScreen();

        renderer.renderEntity(entity);

        screen.stopRenderToScreen();
        renderer.renderScreen(screen);

        Input::update();
        WindowManager::update();
    }
    renderer.cleanUp();
    screen.cleanUp();
    std::cout << "vectors: " << Vector3f::count << std::endl;
    loader.cleanUp();
    WindowManager::close();
    return 0;
}