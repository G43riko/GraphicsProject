//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMANAGER_H
#define GRAPHICSPROJECT_ENTITYMANAGER_H


#include <src/rendering/model/Entity.h>
#include <map>
#include <vector>

typedef std::map<PointerMaterialedModel, std::vector<PointerEntity>> EntitiesList;

class EntityManager {
private:
    EntitiesList entities;
    int count = 0;
    void addModel(PointerMaterialedModel model){
        entities[model] = std::vector<PointerEntity>();
    }
public:
    int size(void){
        return count;
    }
    void addEntity(PointerEntity entity) {
        if (entities.find(entity->getModel()) == entities.end()) {
            addModel(entity->getModel());
        }
        count++;
        entities[entity->getModel()].push_back(entity);
    }
    EntitiesList getEntities(void){
        return entities;
    }
    void update(float delta){
        for (auto it = entities.begin(); it != entities.end(); ++it){ //pre všetky materialy
            if(it -> second.size()){
                auto itEnt = it->second.begin();
                while(itEnt != it->second.end()){ //prejde všetky entity
                    if(itEnt -> get() -> isAlive()){
                        itEnt++;
                    }
                    else{
                        count--;
                        itEnt = it->second.erase(itEnt);
                    }
                }
            }
        }
    }
};


#endif //GRAPHICSPROJECT_ENTITYMANAGER_H
