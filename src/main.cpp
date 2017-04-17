
#include <src/GameEngine.h>
#include <src/core/MainApplication.h>

int main(int argc, char *argv[]){
    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);



    engine.start();
//    engine.setUpApp(new MainApplication());
//    engine.appStart();

    return EXIT_SUCCESS;
}