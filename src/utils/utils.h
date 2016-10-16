//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_UTILS_H
#define GRAPHICSPROJECT_UTILS_H

#include <stdlib.h>
#include <set>

class IdGenerator{
    private:
        static std::set<int> ides;
    public:
        static int getId(void);
};

#endif //GRAPHICSPROJECT_UTILS_H
