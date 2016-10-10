

#include "rendering/WindowManager.cpp"
#include "rendering/shader/EntityShader.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include <memory>
#include "utils/Vectors.cpp"
#include <vector>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"

int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);
    WindowManager::init(800, 600, "Okno");

    Loader * loader = new Loader();
    PointerTexture2D texture(new Texture2D(ContentLoader::loadTexture("res/textures/lena.rgb", 512, 512)));
    PointerMaterial material(new Material(texture));
    PointerRawModel rawModel(loader -> loadToVao(ContentLoader::loadOBJ("res/models/dragon.obj")));
    PointerMaterialedModel model(new MaterialedModel(rawModel, material));
    PointerEntity entity(new Entity(model, PointerVector3f(new Vector3f(0, 0, -5)),
                                           PointerVector3f(new Vector3f(0, 0,  0)),
                                           PointerVector3f(new Vector3f(1, 1,  1))));


    PointerBasicShader guiShader = PointerBasicShader(new EntityShader());
    guiShader -> compileShader();
    Renderer * renderer = new Renderer(guiShader);

    Input::init();

    while (!WindowManager::isCloseRequest()) {
        renderer -> prepare(0, 0, 0, 1);
        entity -> getTransform() -> getRotation() -> y -= 0.03f;


        renderer -> render(entity, guiShader);

        Input::update();
        WindowManager::update();
    }

    //saveBuffer();
    std::cout << "vectors: " << Vector3f::count << std::endl;
    loader -> cleanUp();
    WindowManager::close();
    return 0;
}