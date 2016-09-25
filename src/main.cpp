

#include "rendering/WindowManager.cpp"
#include "rendering/shader/GuiShader.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include "utils/Vectors.cpp"
#include <vector>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.cpp"

void onKeyDown(GLFWwindow * window, int key, int scanCode, int action, int mods){
    if(action == GLFW_PRESS){
        std::cout << "GLFW_PRESS: " << key << std::endl;
    }
    else if(action == GLFW_RELEASE){
        std::cout << "GLFW_RELEASE: " << key << std::endl;
    }
    else if(action == GLFW_REPEAT){
        std::cout << "GLFW_REPEAT: " << key << std::endl;
    }
}
int main(){
    WindowManager::init(800, 600, "Okno");

    Loader * loader = new Loader();

    Material * material = new Material(new Texture2D(ContentLoader::loadTexture("res/textures/lena.rgb", 512, 512)));
    MaterialedModel * model = new MaterialedModel(loader -> loadToVao(Mesh::cube), material);
    Entity * entity = new Entity(model, new Vector3f(0, 0, -5), new Vector3f(0, 0, 0), new Vector3f(1, 1, 1));


    BasicShader * guiShader = new GuiShader();
    guiShader -> compileShader();

    Renderer * renderer = new Renderer(guiShader);

    Input::init(WindowManager::window);

    while (!WindowManager::isCloseRequest()) {
        renderer -> prepare(0, 0, 0, 1);
        //entity -> getTransform() -> getPosition() -> z -= 0.1f;
        renderer -> render(entity, guiShader);

        Input::update();
        WindowManager::update();
    }

    loader -> cleanUp();
    WindowManager::close();
    return 0;
}