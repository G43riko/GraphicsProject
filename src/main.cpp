
#include <src/GameEngine.h>
#include <src/core/MainApplication.h>
#include <src/components/voxel/VoxelApplication.h>
#include <src/utils/Array3D.h>

//static gpointer threadOpenGl(gpointer user_data){
//    printf("aaaaaaaaa\n");
//}

int main(int argc, char *argv[]){

//    Array3D<int, 3, 3, 3> test;
//    for(int i=0 ; i< 3 ; i++) {
//        for (int j = 0; j < 3; j++) {
//            for (int k = 0; k < 3; k++) {
//                test.set(i, j, k, 123456);
//            }
//        }
//    }
//    GThread * threadOGL;
//    threadOGL = g_thread_new(NULL, threadOpenGl, nullptr);
//    g_thread_join(threadOGL);

    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(new VoxelApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);
    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();
    return EXIT_SUCCESS;
}