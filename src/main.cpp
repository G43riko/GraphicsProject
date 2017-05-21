
#include <src/GameEngine.h>
#include <src/misc/MainApplication.h>
#include <ctime>
#include <src/components/voxel_old/VoxelApplication.h>
#include <chrono>
#include <src/components/voxel/chunks/ChunkGenerator.h>
//#include <src/utils/Array3D.h>


long int getTime(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void testVectors(){
    long int a, b;
    uint num = 1000000;
    int sum = 0;
    std::vector<int> vec;
    for(uint i=0 ; i<num ; i++){vec.push_back(i);}

    b = getTime();
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++){sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;sum += *it; sum -= *it; sum += *it, sum -= *it;}
    printf("b: %lu\n", getTime() - b);
    sum = 0;

    a = getTime();
    for(uint i=0 ; i<vec.size() ; i++){sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i];}
    printf("a: %lu\n", getTime() - a);


}

int main(int argc, char *argv[]){
//    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
    BasicEngine engine = BasicEngine(new VoxelApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);
    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();
    return EXIT_SUCCESS;
}