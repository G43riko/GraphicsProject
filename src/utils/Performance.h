//
// Created by gabriel on 22.4.2017.
//

#ifndef GAMEENGINE_PERFORMANCE_H
#define GAMEENGINE_PERFORMANCE_H

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

typedef struct gUsage{
    long userTime;
    long systemTime;
    long usedMemory;
    void show(void){
        printf("user time: %ldms, system time: %ldms, used memory: %ldkb, %ld\n", userTime / 1000L, systemTime / 1000L, usedMemory, usedMemory / 1024);
    }
}GUsage;

inline void getUsage(GUsage * data){
    struct rusage usage;
    if(getrusage(RUSAGE_SELF, &usage) == 0){
        data -> userTime = usage.ru_utime.tv_sec * 1000000L + usage.ru_utime.tv_usec;
        data -> systemTime = usage.ru_stime.tv_sec * 1000000L + usage.ru_stime.tv_usec;
        data -> usedMemory = usage.ru_maxrss;
    }
}

#endif //GAMEENGINE_PERFORMANCE_H
