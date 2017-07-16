//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_MASTER_H
#define GRAPHICSPROJECT_MASTER_H

#include <src/components/postProccessing/PostFxMaster.h>
#include <src/components/voxel/VoxelMaster.h>
#include "../components/shadows/ShadowMaster.h"
#include "../components/gui/GuiMaster.h"
#include "../components/sky/SkyBoxMaster.h"
#include "../components/particles/ParticleMaster.h"
#include "../components/water/WaterMaster.h"
#include "../components/entities/EntityMaster.h"



class EntityMaster;

class Master {
    GuiMaster *guiMaster            = nullptr;
    WaterMaster *waterMaster        = nullptr;
    SkyBoxMaster *skyBoxMaster      = nullptr;
    PostFxMaster *postFxMaster      = nullptr;
    ShadowMaster *shadowMaster      = nullptr;
    EntityMaster *entityMaster      = nullptr;
    ParticleMaster *particleMaster  = nullptr;
    VoxelMaster *voxelMaster        = nullptr;

    MasterOptions options;

    void initOptions(void) {
        options.useShadows = false;
        options.useEntities = true;
        options.useParticles = true;
        options.useSkybox = true;
        options.useWaters = true;
        options.usePostFx = false;
        options.useVoxels = true;
        options.useGuis = true;
        options.useTextures = false;
        options.useNormals = false;
        options.useLights = false;
        options.useSpeculars = false;
        options.useEnviromentals = false;
    };
public:
    inline Master(void){
        initOptions();
    };

    void updateProjectionMatrix(const BasicCamera& camera);

    void cleanUp(void);

    inline void update(float delta){
        if(waterMaster){
            waterMaster -> update(delta);
        }
    }

    void init(Loader loader, int width, int height, BasicCamera& camera, PointerBasicShader shadowShader);

    //SETTERS
    inline void setPostFx(bool val){ options.usePostFx = val; }
    inline void setShadow(bool val){ options.useShadows = val; }
    inline void setWater(bool val){ options.useWaters = val; }
    inline void setSky(bool val){ options.useSkybox = val; }

    //GETTERS
    inline GuiMaster * getGui(void)const {return guiMaster; }
    inline WaterMaster * getWater(void)const {return waterMaster; }
    inline PostFxMaster * getPostFx(void)const {return postFxMaster; }
    inline ShadowMaster * getShadow(void)const {return shadowMaster; }
    inline EntityMaster * getEntity(void)const {return entityMaster; }
    inline SkyBoxMaster * getSkyBox(void)const { return skyBoxMaster; }
    inline ParticleMaster * getParticle(void)const {return particleMaster; }
    inline VoxelMaster * getVoxel(void)const {return voxelMaster; }

    inline bool useParticles(void) const{return options.useParticles; }
    inline bool useShadows(void) const{return options.useShadows; }
    inline bool useSkybox(void) const{return options.useSkybox; }
    inline bool useWaters(void) const{return options.useWaters; }
    inline bool usePostFx(void) const{return options.usePostFx; }
    inline bool useSky(void) const{return options.useSkybox; };
    inline bool useVoxels(void) const{return options.useVoxels; };
};
#endif //GRAPHICSPROJECT_MASTER_H
