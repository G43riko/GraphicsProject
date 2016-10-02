

#include "rendering/WindowManager.cpp"
#include "rendering/shader/EntityShader.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include "utils/Vectors.cpp"
#include <vector>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"


void saveBuffer(){
    unsigned char *Buff = new unsigned char[512 * 512 * 3];
    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, 512, 512, GL_RGB, GL_UNSIGNED_BYTE, Buff);


    std::ofstream raw("res/textures/result.rgb", std::ios::binary);
    raw.write(reinterpret_cast<char *>(Buff), sizeof(Buff));
    raw.close();

    /*
    FILE *Out = fopen(filename, "wb");
    if (!Out)
        return;

    fwrite(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, Out);
    fwrite(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, Out);
    fwrite(Buff, windowWidth*windowHeight * 3, 1, Out);
    fclose(Out);

    delete[] Buff;
    */
}

template<typename T> class GVector3 : public GVector<T>{
    public:
        template<typename S>
        GVector3(S x, S y, S z) : GVector3(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)){}
        GVector3(GVector3<T> * a) : GVector3(a -> getX(), a -> getY(), a -> getZ()) {};
        GVector3(T x, T y, T z){
            this -> size = 3;
            this -> data = new T[this -> size]{x, y, z};
        }

        T getX(){return this -> data[0];}
        T getY(){return this -> data[1];}
        T getZ(){return this -> data[2];}
};

int main(void){
    //ContentLoader::loadOBJ("res/models/plane.obj") -> show();
    //exit(1);
    WindowManager::init(800, 600, "Okno");

    Loader * loader = new Loader();

    Material * material = new Material(new Texture2D(ContentLoader::loadTexture("res/textures/barrel.rgb", 512, 512)));
    //MaterialedModel * model = new MaterialedModel(loader -> loadToVao(Mesh::cube), material);
    MaterialedModel * model = new MaterialedModel(loader -> loadToVao(ContentLoader::loadOBJ("res/models/barrel.obj")), material);
    Entity * entity = new Entity(model, new Vector3f(0, 0, -5), new Vector3f(0, 0, 0), new Vector3f(1, 1, 1));


    BasicShader * guiShader = new EntityShader();
    guiShader -> compileShader();

    Renderer * renderer = new Renderer(guiShader);

    Input::init();

    while (!WindowManager::isCloseRequest()) {
        renderer -> prepare(0, 0, 0, 1);
        //entity -> getTransform() -> getPosition() -> z -= 0.1f;
        entity -> getTransform() -> getRotation() -> y -= 0.03f;
        renderer -> render(entity, guiShader);

        Input::update();
        WindowManager::update();
    }

    //saveBuffer();

    loader -> cleanUp();
    WindowManager::close();
    return 0;
}