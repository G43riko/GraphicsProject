//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/rendering/model/Entity.h>
#include "Light.h"
#include <map>
#include <src/rendering/Renderer.h>

class Scene {
    private:
        PointerRawModel guiModel = nullptr;
        PointerRawModel sphereModel = nullptr;
        PointerRawModel skyModel = nullptr;
        CubeTexture sky;
        static std::vector<GLfloat> guiVertices;
        constexpr static float SIZE = 500;
        static std::vector<float> VERTICES;
        std::vector<PointerEntity> entities;
        std::vector<PointerLight> lights;
    public:
        Scene(Loader, CubeTexture);
        void addLight(PointerLight light){
            lights.push_back(light);
        }
        void addEntity(PointerEntity entity){
            entities.push_back(entity);
        }

        std::vector<PointerLight> getLights(){
            return lights;
        };

        std::vector<PointerEntity> getEntities(){
            return entities;
        };

        PointerRawModel getGuiModel(void){
            if(!guiModel)
                std::cout << "nieje guiModel\n";
            return guiModel;
        };
        CubeTexture getSky(void){
            return sky;
        }
        void cleanUp(){
            sky.cleanUp();
        }
        PointerRawModel getSphereModel(void){
            if(!sphereModel)
                std::cout << "nieje sphereModel\n";
            return sphereModel;
        };
        PointerRawModel getSkyModel(void){
            if(!skyModel)
                std::cout << "nieje skyModel\n";
            return skyModel;
        };
};


#endif //GRAPHICSPROJECT_SCENE_H
