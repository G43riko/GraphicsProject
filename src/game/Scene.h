//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/core/BasicScene.h>

class BasicScene;

class Scene : public BasicScene{
    private:
        PointerRawModel sphereModel = nullptr;
    public:
        inline Scene(Loader loader, PointerCubeTexture sky = nullptr) : BasicScene(sky){}

        void addObject(PointerGameObject object) override{
            objects.push_back(object);
            entities.addEntity(object->getObject());
        }
        void removeObject(PointerGameObject object){
            for(auto iter = objects.begin(); iter != objects.end(); ++iter){
                if( *iter == object ){
                    objects.erase(iter);
                    break;
                }
            }
            entities.removeEntity(object ->getObject());
        };
        void update(float delta) override{
            particles.update(delta);

            if(objects.size()){
                auto itObj = objects.begin();
                while(itObj != objects.end()){
                    itObj -> get() -> update(delta);
                    itObj++;
                }
            }
            entities.update(delta);
        };

        void cleanUp(void) override{
            sky -> cleanUp();
        };

        inline PointerRawModel getSphereModel(void) const{
            return sphereModel;
        };
};


#endif //GRAPHICSPROJECT_SCENE_H
