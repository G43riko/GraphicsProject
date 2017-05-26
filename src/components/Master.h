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

    void initOptions(void);
public:
    Master(void);
    void updateProjectionMatrix(PointerCamera camera);

    void cleanUp(void);

    void update(float delta);

    void init(Loader loader, int width, int height, PointerCamera camera, PointerBasicShader shadowShader);

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
