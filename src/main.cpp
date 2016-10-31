

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

void test(std::string fileName){
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, "res/textures/" + fileName);

    // If there's an error, display it.
    if(error != 0) {
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    std::cout << width << " " << height << std::endl;
}

int main(void){
    test("brickWall.png");
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);

    WindowManager::init(800, 600, "Okno", true);
    Input::init();

    Loader loader = Loader();
    Renderer renderer = Renderer();

    auto diffuse = ContentLoader::loadTexturePNG("res/textures/texture.png");
    auto normal = ContentLoader::loadTexturePNG("res/textures/textureNormal.png");
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/box.obj")));
    auto model = createMaterialedModel(rawModel, createMaterial(diffuse, normal));
    auto entity = createEntity(model, Vector3f(0, 0, -10), Vector3f(0, 0, 0), Vector3f(1, 1, 1));

    auto screen = Screen(WindowManager::width, WindowManager::height, loader);
    PointerLight light = createLight(createVector3f(0, 0, 0), createVector3f(1, 1, 1), Vector3f(1.0f, 0.01f, 0.002f));
    std::vector<PointerLight> ligts{light/*,
                                    createLight(createVector3f(200, 10,  200), createVector3f(0, 0, 1))*/};

    float time = 0;
    while (!WindowManager::isCloseRequest()) {
        renderer.prepare(0, 0, 0, 1);
        time+= 0.004;
        renderer.init3D();
        light->getPosition()->z = cos(time) * 20 - 10;
        entity -> getTransform() -> getRotation() -> rotate(Vector3f(0.00f, 0.005f, 0.00f));

        //renderer.renderEntity(entity);
        renderer.renderObject(entity, ligts);

        /*
        screen.startRenderToScreen();

        //renderer.renderEntity(entity);
        renderer.renderObject(entity, ligts);

        screen.stopRenderToScreen();
        renderer.renderScreen(screen);
        */
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