
#include <src/GameEngine.h>
#include <src/misc/MainApplication.h>
#include <src/components/voxel_old/VoxelApplication.h>
#include <chrono>
//#include <src/utils/Array3D.h>


long int getTime(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int main(int argc, char *argv[]){
    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(new VoxelApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);
    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();
    return EXIT_SUCCESS;
}