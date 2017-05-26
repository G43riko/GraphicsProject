//
// Created by gabriel on 22.5.2017.
//

#ifndef GAMEENGINE_CPP11_H
#define GAMEENGINE_CPP11_H

#if __cplusplus < 201103L || _MSC_VER < 1600
    #define USE_CPP11_FAKE_KEYWORD
#endif

#ifdef USE_CPP11_FAKE_KEYWORD
    #define constexpr const
    #define nullptr NULL
#endif

#endif //GAMEENGINE_CPP11_H
