//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_ENTITYMANAGER_H
#define GRAPHICSPROJECT_ENTITYMANAGER_H


#include <src/rendering/model/Entity.h>


class EntityManager {
private:
    EntitiesList entities;
    int count = 0;
    inline void addModel(PointerMaterialedModel model){
        entities[model] = std::vector<PointerEntity>();
    }
public:
    inline int size(void) const{ return count; }
    inline void addEntity(const PointerEntity& entity) {
        if(!MAP_CONTAINS_KEY(entities, entity -> getModel())){
            addModel(entity->getModel());
        }
        count++;
        entities[entity->getModel()].push_back(entity);
    }

    inline void removeEntity(const PointerEntity& entity){
        if(MAP_CONTAINS_KEY(entities, entity->getModel())){
            return;
        }
        std::vector<PointerEntity> actualEntities = entities[entity -> getModel()];

        ITERATE_VECTOR_ITERATOR_AUTO(actualEntities, iter){
            if( *iter == entity ){
                actualEntities.erase(iter);
                break;
            }
        }
    }
    inline const EntitiesList& getEntities(void) const{
        return entities;
    }
    inline void update(float delta){
        ITERATE_MAP_AUTO(entities, it){ // pre všetky materialy
            if(it -> second.size()){
                ITERATE_VECTOR_ITERATOR_AUTO_ENDLESS(it->second, itEnt){ //prejde všetky entity
                    if((*itEnt)-> isAlive()){
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
