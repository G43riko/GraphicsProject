//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_GRANDOM_H
#define GAMEENGINE_GRANDOM_H

#include <random>
#include <ctime>

namespace GRandom{
    std::mt19937_64 randomEngine;

    void init(void){
        randomEngine.seed(std::time(nullptr));
    }

    int64_t intInRange(int64_t low, int64_t high){
        std::uniform_int_distribution<int64_t> dist(low, high);
        return dist(randomEngine);
    }

    float floatInRange(float low, float high){
        std::uniform_real_distribution<float> dist(low, high);
        return dist(randomEngine);
    }

    template <typename Engine>
    class Generator{
    private:
        Engine _randomEngine;
    public:
        Generator(void){
            _randomEngine.seed(std::time(nullptr));
        }
        int64_t intInRange(int64_t low, int64_t high){
            std::uniform_int_distribution<int64_t> dist(low, high);
            return dist(_randomEngine);
        }

        float floatInRange(float low, float high){
            std::uniform_real_distribution<float> dist(low, high);
            return dist(_randomEngine);
        }
        template <typename T>
        T numberInRange(T low, T high){
            std::uniform_real_distribution<T> dist(low, high);
            return dist(_randomEngine);
        }
    };
}
#endif //GAMEENGINE_GRANDOM_H
