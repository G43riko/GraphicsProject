//
// Created by gabriel on 8.5.2017.
//

#ifndef GAMEENGINE_THREADUTILS_H
#define GAMEENGINE_THREADUTILS_H

#include <glib/gtypes.h>
#include <glib/gthread.h>

struct funcArgs{
    void * func;
    void * args;
};
/**
 * Táto funkcia sa vola v novom vlakne a spusti funkciu ktorú dostane na vstupe
 *
 * @param user_data
 * @return
 */
inline gpointer unitedFunc(gpointer user_data){
    struct funcArgs * data = static_cast<struct funcArgs *>(user_data);
    ((void (*)(void *))data -> func)(data -> args);
    return nullptr;
}

/**
 * Táto funkcia dostane na vstup funkciu ktorú má spustiť v novom vlákne a jej argumenty
 *
 * @param func
 * @param pointer
 * @return
 */
void * callAsyncFunc(void * func, void * pointer){
    struct funcArgs arguments = {func, pointer};
    return g_thread_new(nullptr, unitedFunc, &arguments);
}

#endif //GAMEENGINE_THREADUTILS_H
