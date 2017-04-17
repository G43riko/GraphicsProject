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
#include "../components/entities/EntityMaster.h"
#include "../components/water/WaterMaster.h"

typedef struct masterOptions{
    bool useShadows;
    bool useGuis;
    bool useSkybox;
    bool useParticles;
    bool useEntities;
    bool useWaters;
    bool useVoxels;
    bool usePostFx;
    bool useTextures;
    bool useNormals;
    bool useLights;
    bool useSpeculars;
    bool useEnviromentals;
}MasterOptions;

class EntityMaster;
class Master {
private:
    GuiMaster *guiMaster            = nullptr;
    WaterMaster *waterMaster        = nullptr;
    SkyBoxMaster *skyBoxMaster      = nullptr;
    PostFxMaster *postFxMaster      = nullptr;
    ShadowMaster *shadowMaster      = nullptr;
    EntityMaster *entityMaster      = nullptr;
    ParticleMaster *particleMaster  = nullptr;
    VoxelMaster *voxelMaster        = nullptr;

    MasterOptions options;

    void initOptions(void);
public:
    Master(void);
    void updateProjectionMatrix(PointerCamera camera);

    void cleanUp(void);

    void update(float delta);

    void init(Loader loader, int width, int height, PointerCamera camera, PointerBasicShader shadowShader, PointerBasicShader particleShader);

    //SETTERS
    inline void setPostFx(bool val){ options.usePostFx = val; }
    inline void setShadow(bool val){ options.useShadows = val; }
    inline void setWater(bool val){ options.useWaters = val; }
    inline void setSky(bool val){ options.useSkybox = val; }

    //GETTERS
    inline GuiMaster * getGui(void){return guiMaster; }
    inline WaterMaster * getWater(void){return waterMaster; }
    inline PostFxMaster * getPostFx(void){return postFxMaster; }
    inline ShadowMaster * getShadow(void){return shadowMaster; }
    inline EntityMaster * getEntity(void){return entityMaster; }
    inline SkyBoxMaster * getSkyBox(void){ return skyBoxMaster; }
    inline ParticleMaster * getParticle(void){return particleMaster; }
    inline VoxelMaster * getVoxel(void){return voxelMaster; }

    inline bool useParticles(void){ return options.useParticles; }
    inline bool useShadows(void){ return options.useShadows; }
    inline bool useSkybox(void){ return options.useSkybox; }
    inline bool useWaters(void){ return options.useWaters; }
    inline bool usePostFx(void){ return options.usePostFx; }
    inline bool useSky(void){ return options.useSkybox; };
    inline bool useVoxels(void){ return options.useVoxels; };
};
#endif //GRAPHICSPROJECT_MASTER_H
