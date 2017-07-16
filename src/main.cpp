#include <src/core/BasicEngine.h>
#include <src/misc/MainApplication.h>
#include <src/misc/PreviewApplication.h>
#include <src/components/voxel_old/VoxelApplication.h>
#include <SFML/Graphics.hpp>
#include <src/core/SfmlEngine.h>

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
    for(uint i=0 ; i<vec.size() ; i++){sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i]; sum += vec[i];
                                       sum -= vec[i]; sum += vec[i], sum -= vec[i]; sum += vec[i]; sum -= vec[i];
                                       sum += vec[i], sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i];
                                       sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i]; sum -= vec[i];
                                       sum += vec[i]; sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i];
                                       sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i]; sum -= vec[i];
                                       sum += vec[i]; sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i];
                                       sum -= vec[i]; sum += vec[i]; sum -= vec[i]; sum += vec[i]; sum -= vec[i];
                                       sum += vec[i]; sum -= vec[i]; sum += vec[i], sum -= vec[i]; sum += vec[i];}
    printf("a: %lu\n", getTime() - a);
}

void testColorOutput(){
}
int testSFML() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

int main(int argc, char *argv[]){
//    testSFML();
//    return 0;
    testColorOutput();
//    BasicEngine engine = BasicEngine(new PreviewApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
    BasicEngine engine = BasicEngine(new VoxelApplication(), RES_X_DEFAULT, RES_Y_DEFAULT);
//    BasicEngine engine = BasicEngine(nullptr, RES_X_DEFAULT, RES_Y_DEFAULT);

//    SfmlEngine engine = SfmlEngine(new MainApplication(), RES_X_DEFAULT, RES_Y_DEFAULT, "Game Engine");
    engine.start();
//    SfmlEngine::test();

//    engine.setUpApp(new MainApplication());
//    engine.appStart();
    return EXIT_SUCCESS;
}