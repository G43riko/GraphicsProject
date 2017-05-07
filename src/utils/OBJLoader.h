//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_OBJLOADER_H
#define GAMEENGINE_OBJLOADER_H

#include <string>
#include <map>
#include <glib/gtypes.h>
#include <glib/gthread.h>
#include <src/rendering/model/Mesh.h>
#include <src/rendering/model/RawModel.h>
#include "FileLoader.h"
#include "Loader.h"


class OBJLoader{
private:
    SOMap loadedObjects;
    GThread * objLoaderThread = nullptr;

    inline static gpointer loadModels(gpointer user_data){
        SOMap * titles = static_cast<SOMap*>(user_data);
        for(auto title : *titles){
            if(IS_NULL(title .second -> mesh)){
                title .second -> mesh = ContentLoader::loadOBJ(title . second -> title);
            }
        }
        return nullptr;
    }
public:
    inline OBJLoader(VectorS titles){
        setTitles(titles);
    };
    inline void setTitles(VectorS titles){
        for(std::string title : titles){
            if(!MAP_CONTAINS_KEY(loadedObjects, title)){
                loadedObjects[title] = new objectType(MODELS_FOLDER + title + MODELS_EXTENSION, nullptr);
            }
        }
    }

    inline void startLoadSynch(void){
        objLoaderThread = g_thread_new(THREAD_TITLE, loadModels, &loadedObjects);

        g_thread_unref(objLoaderThread);
        delete  objLoaderThread;
        objLoaderThread = nullptr;
    }

    inline void startLoadAsynch(void){
        objLoaderThread = g_thread_new(THREAD_TITLE, loadModels, &loadedObjects);
    }
    inline void cleanUp(void){
        for(auto i : loadedObjects){
            delete i.second;
        }
    }
    inline void waitLoadAsynch(void){
        g_thread_join(objLoaderThread);
        g_thread_unref(objLoaderThread);
        delete  objLoaderThread;
        objLoaderThread = nullptr;
    }
    inline PointerRawModel getRawModel(Loader loader, std::string title){
        if(MAP_CONTAINS_KEY(loadedObjects, title)){
            return loader.loadToVao(loadedObjects[title] -> mesh);;
        }
        return nullptr;
    }
    inline PointerMesh getMesh(std::string title){
        if(MAP_CONTAINS_KEY(loadedObjects, title)){
            return loadedObjects[title]->mesh;
        }
        return nullptr;
    }
};

#endif //GAMEENGINE_OBJLOADER_H
