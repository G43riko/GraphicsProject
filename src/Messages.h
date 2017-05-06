//
// Created by gabriel on 6.5.2017.
//

#ifndef GAMEENGINE_MESSAGES_H
#define GAMEENGINE_MESSAGES_H

#include <string>

enum Messages{
    WRONG_DIRECTION,
    CANT_FIND_SHADER,
};

inline const char * getMessage(Messages type){
    switch(type){
        case Messages::WRONG_DIRECTION :
            return "Zlý smer roviny";
        case Messages::CANT_FIND_SHADER :
            return "Nenašiel sa shader";
        default:
            return "Neznámy typ správy";
    }
}


#endif //GAMEENGINE_MESSAGES_H
