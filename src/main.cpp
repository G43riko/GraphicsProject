

#include "rendering/WindowManager.cpp"
#include "rendering/shader/EntityShader.cpp"
#include "rendering/shader/PostFxShader.cpp"
#include "rendering/shader/ObjectShader.cpp"
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

class v3{
public:
    float x, y, z;
    v3(float x, float y, float z) : x(x), y(y), z(z){};
    void show(){
        std::cout << "[" << x << "x" << y << "x" << z << "]" << std::endl;
    }

};


int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);
    WindowManager::init(800, 600, "Okno");

    Loader * loader = new Loader();
    //PointerTexture2D texture(new Texture2D(ContentLoader::loadTexture("res/textures/lena.rgb", 512, 512)));
    PointerTexture2D texture(new Texture2D(ContentLoader::loadTexture("res/textures/barrel.rgb", 1024, 1024)));
    PointerMaterial material(new Material(texture));
    //PointerRawModel rawModel(loader -> loadToVao(ContentLoader::loadOBJ("res/models/dragon.obj")));
    PointerRawModel rawModel(loader -> loadToVao(ContentLoader::loadOBJ("res/models/barrel.obj")));
    //PointerRawModel rawModel(loader -> loadToVao(Mesh::plane));
    PointerMaterialedModel model(new MaterialedModel(rawModel, material));
    PointerEntity entity(new Entity(model, PointerVector3f(new Vector3f(0, 0, -5)),
                                           PointerVector3f(new Vector3f(0, 0,  0)),
                                           PointerVector3f(new Vector3f(1, 1,  1))));


    Renderer * renderer = new Renderer();
    renderer -> addShader("entityShader", PointerBasicShader(new EntityShader()));
    renderer -> addShader("postFxShader", PointerBasicShader(new PostFxShader()));
    renderer -> addShader("objectShader", PointerBasicShader(new ObjectShader()));

    renderer -> setCamera(PointerCamera(new Camera()));

    ;
    std::vector<PointerLight> ligts{PointerLight(new Light(new Vector3f(200,  10, -200), new Vector3f(1, 0, 0))),
                                    PointerLight(new Light(new Vector3f(200, 10, 200), new Vector3f(0, 0, 1)))};


    Input::init();

    Fbo * fbo = new Fbo(WindowManager::width, WindowManager::height, Fbo::DEPTH_RENDER_BUFFER);
    PostProccessing * pp = new PostProccessing(loader, WindowManager::width, WindowManager::height);
    Screen * screen = new Screen(WindowManager::width, WindowManager::height, loader);
    while (!WindowManager::isCloseRequest()) {
        renderer -> prepare(0, 0, 0, 1);
        renderer -> init3D();
        entity -> getTransform() -> getRotation() -> y -= 0.03f;
        screen -> startRenderToScreen();

        //fbo -> bindFrameBuffer();

        //renderer -> renderEntity(entity);
        renderer -> renderObject(entity, ligts);

        screen -> stopRenderToScreen();
        renderer -> renderScreen(screen);


        //fbo -> unbindFrameBuffer();

        //pp -> doPostProcessing(fbo -> getColourTexture());
        //pp -> doPostProcessing(texture -> getTextureID());


        Input::update();
        WindowManager::update();
    }

    pp -> cleanUp();
    fbo -> cleanUp();
    //saveBuffer();
    std::cout << "vectors: " << Vector3f::count << std::endl;
    loader -> cleanUp();
    WindowManager::close();
    return 0;
}