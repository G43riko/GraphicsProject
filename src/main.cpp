
#include "rendering/WindowManager.cpp"
#include "rendering/Renderer.cpp"
#include "rendering/model/Mesh.h"
#include "utils/Loader.cpp"
#include "utils/Input.cpp"
#include "src/components/postProccessing/Screen.cpp"
#include <memory>
#include "utils/Vectors.cpp"
#include <vector>
#include <src/components/postProccessing/Fbo.h>
#include <src/components/postProccessing/PostProccessing.h>
#include <src/components/water/WaterFrameBuffer.h>
#include <src/components/terrain/Terrain.h>
#include <src/components/movement/FpsView.h>
#include <src/components/movement/TopView.h>
#include <src/game/Ball.h>
#include "rendering/material/Texture2D.cpp"
#include "rendering/material/Material.h"
#include <time.h>
#include <src/game/Environment.h>
#include <src/game/Arrow.h>
#include <src/components/shadows/ShadowMaster.h>
#include <src/components/terrain/HeightGenerator.h>
#include <src/components/entities/EntityManager.h>
#include <src/components/particles/ParticleManager.h>
#include <src/core/BasicEngine.h>
#include <src/core/MainApplication.h>
#include <src/GUI/BasicGtkGui.h>


int main(int argc, char *argv[]){
    BasicEngine engine = BasicEngine(nullptr, 800, 600);

    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();


    return 0;
}