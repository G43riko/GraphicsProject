
#include <src/GameEngine.h>
#include <src/core/MainApplication.h>
#include <src/components/voxel/VoxelApplication.h>
#include <src/utils/Array3D.h>
#include <src/components/voxel/ChunkManager.h>


void testAbstractVoxels(void){
    ChunkManager chunks(59, 79, 1);
}

int main(int argc, char *argv[]){
    testAbstractVoxels();
    return 0;

//    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
    BasicEngine engine = BasicEngine(new VoxelApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);
    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();
    return EXIT_SUCCESS;
}