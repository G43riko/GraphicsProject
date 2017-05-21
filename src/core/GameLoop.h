//
// Created by gabriel on 19.5.2017.
//

#ifndef GAMEENGINE_GAMELOOP_H
#define GAMEENGINE_GAMELOOP_H


#include <zconf.h>
#include <chrono>

#define MICROSECONDS 1000000
class GameLoop{
    typedef void (*UpdateFunction)(float);
    typedef void (*SecondUpdate)(int);
    typedef bool (*EndFunction)(void);

    UpdateFunction _updateFunction;
    EndFunction _endFunction;
    SecondUpdate _secondUpdate;
    const uint _FPS, _frameTime;
    bool _running = false;

    inline void stop(void){
        _running = false;
    }
    inline int getMicroseconds(void){
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    inline int getNanoseconds(void){
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    inline void update(void){
        int lastTimeCycle = getNanoseconds();
        int lastTimeOutput = getMicroseconds();

        long long int unprocessedTicks = 0;
        int FPS = 0, ticks = 0;
        while(FPS >= 0){
            int nowTimeCycle = getNanoseconds();
            printf("_frameTime: %d\n", _frameTime);
            printf("(nowTimeCycle - lastTimeCycle): %d\n", (nowTimeCycle - lastTimeCycle));
            unprocessedTicks += (nowTimeCycle - lastTimeCycle) / (_frameTime);
            lastTimeCycle = nowTimeCycle;

            printf("unprocessedTicks: %llu\n", unprocessedTicks);
            while(unprocessedTicks >= 1){
                ticks++;
                unprocessedTicks--;
            }
            FPS++;

            if(getMicroseconds() - lastTimeOutput > MICROSECONDS){
                lastTimeOutput += MICROSECONDS;

                printf("ticks: %d, FPS: %d\n", ticks, FPS);
                FPS = ticks = 0;
            }

        }
    }
    inline void update2(void){
        auto start = std::chrono::high_resolution_clock::now();
        auto startLoopTime = start, middleLoopTime = start, endLoopTime = start;
        float delta = 1;
        uint fps;
        long long microseconds, loopTime;

        while(_running){
            fps = 0;
            start = std::chrono::high_resolution_clock::now();
            do{
                startLoopTime = std::chrono::high_resolution_clock::now();
                //UPDATE
                fps++;
                if(_running){
                    if(_endFunction()){
                        stop();
                    }
                }
                _updateFunction(delta);

                //////////SYS
                middleLoopTime = std::chrono::high_resolution_clock::now();
                loopTime = std::chrono::duration_cast<std::chrono::microseconds>(middleLoopTime - startLoopTime).count();
                if(loopTime <= _frameTime){
                    usleep((uint)(_frameTime - loopTime));
                }
                endLoopTime = std::chrono::high_resolution_clock::now();
                microseconds = std::chrono::duration_cast<std::chrono::microseconds>(endLoopTime - start).count();

                delta = (float)_frameTime /  (float)std::chrono::duration_cast<std::chrono::microseconds>(endLoopTime - startLoopTime).count();

            } while(microseconds < 1000000);
            _secondUpdate(fps);
        }
    }
public:
    inline GameLoop(UpdateFunction updateFunction, uint FPS, EndFunction endFunction, SecondUpdate secondUpdate) :
            _updateFunction(updateFunction),
            _endFunction(endFunction),
            _secondUpdate(secondUpdate),
            _FPS(FPS),
            _frameTime(MICROSECONDS / _FPS){}
    inline void start(void){
        _running = true;
        update();
    }
};

#endif //GAMEENGINE_GAMELOOP_H
