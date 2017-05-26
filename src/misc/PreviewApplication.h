//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_PREVIEWAPPLICATION_H
#define GAMEENGINE_PREVIEWAPPLICATION_H

#include "src/core/BasicApplication.h"
#include <src/components/movement/ModelView.h>
#include <src/rendering/model/models/Sphere.h>
#include <src/components/effectors/FromToEffector.h>
#include <src/components/effectors/CircleEffector.h>
#include <src/components/LensFlares/FlareTexture.h>
#include <src/components/LensFlares/FlareManager.h>

/*
 *  +     trieda Effector - bude upravovať ciel podla nejakých preferencií
 *  +        vie rotovať v nejakej vzidalenosti okolo niečoho iného
 *  +        vie sa posúvať z jedného bodu do druhého
 *  upravy:
 *      pozadie
 *          farba
 *          obloha
 *      automatická rotácia
 *      možnosť načítať 3D objekt
 *      meniť texturu 3D objektu
 *          obrazok
 *          normály
 *          material
 *              farba
 *              odražanlivost
 *              ....
 *      pridať rotujuje svetla
 *          pocet
 *          vzdialenost
 *          rychlosť
 *
 */
class PreviewApplication : public BasicApplication{
    Effector * effector = nullptr;
    FlareManager *flares = nullptr;
    FlareTexture * flareText = nullptr;
public:
    inline void loadContent(void) override {
        const PointerCubeTexture skyTexture = TextureManager::instance.createCubeTexture("sky");
        getScene()->setSky(skyTexture);

        const PointerTexture2D diffuse = TextureManager::instance.createTexture2D("res/textures/texture.png");
        const PointerTexture2D normal = TextureManager::instance.createTexture2D("res/textures/textureNormal.png");
        const PointerMaterial material = Material::create(diffuse, normal);

        Sphere sphereMod(3, 36, 36);
        PointerMaterialedModel model = MaterialedModel::create(getLoader().loadToVao(sphereMod.getMesh()), material);
        PointerEntity sphereEntity = Entity::create(model,
                                                    Vector3f(0, 0, 0),
                                                    Vector3f(0, 0, 0),
                                                    Vector3f(1, 1, 1));
        getScene() -> addEntity(sphereEntity);

        ////EFFECTORS

//        effector = new FromToEffector(Vector3f(0, 0, -2), Vector3f(0, 0, 2), sphereEntity);
//        effector = new CircleEffector(sphereEntity);

        ////FLARES

//        const PointerTexture2D flareText2 = TextureManager::instance.createTexture2D("res/textures/flares/tex2.png");
//        const PointerTexture2D flareText3 = TextureManager::instance.createTexture2D("res/textures/flares/tex3.png");
//        const PointerTexture2D flareText4 = TextureManager::instance.createTexture2D("res/textures/flares/tex4.png");
//        const PointerTexture2D flareText5 = TextureManager::instance.createTexture2D("res/textures/flares/tex5.png");
//        const PointerTexture2D flareText7 = TextureManager::instance.createTexture2D("res/textures/flares/tex7.png");
//        const PointerTexture2D flareText8 = TextureManager::instance.createTexture2D("res/textures/flares/tex8.png");
        const PointerTexture2D flareText6 = TextureManager::instance.createTexture2D("res/textures/flares/tex6.png");
        flareText = new FlareTexture(flareText6 -> getTextureID(), {}, {0.5f, 0.5f}, 0.5);
        std::vector<FlareTexture*> flareTextures;
        flareTextures.push_back(flareText);
//        flareTextures.push_back(FlareTexture(flareText4 -> getTextureID(), {}, {0.23f, 0.23f}, 0.5));
//        flareTextures.push_back(FlareTexture(flareText2 -> getTextureID(), {}, {0.1f, 0.1f}, 0.5));
//        flareTextures.push_back(FlareTexture(flareText7 -> getTextureID(), {}, {0.5f, 0.5f}, 0.5));

        getScene() -> addEntity(Entity::create(model,
                                               Vector3f(50, 50, 50),
                                               Vector3f(0, 0, 0),
                                               Vector3f(1, 1, 1)));
        ITERATE_VECTOR(flareTextures, i){
//            getRenderer().addTexture(flareTextures[i]);
        }

        flares = new FlareManager(0.4f, flareTextures);

    }
    void init(BasicGtkGui * gui) override{
        setRenderer(new Renderer(getLoader(), WindowManager::width, WindowManager::height));
        setScene(new Scene(getLoader()));
        setView(new ModelView(getRenderer().getActualCamera()));
    };

    void update(float delta) override{
        updateApp(delta);
        CHECK_AND_CALL(effector, update(delta));
    }

    inline void render(void) override {
        flares->render(*getRenderer().getActualCamera(), {50, 50, 50});
        getRenderer().renderScene(((Scene *) getScene()));
    }
    void cleanUp(void) override {
        DEBUG("maže sa renderer v voxel_old application");
        TextureManager::instance.cleanUp();
    };
};
#endif //GAMEENGINE_PREVIEWAPPLICATION_H
