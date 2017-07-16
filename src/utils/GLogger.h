//
// Created by gabriel on 30.6.2017.
//

#ifndef GAMEENGINE_GLOGGER_H
#define GAMEENGINE_GLOGGER_H


#include <string>
#include <iosfwd>

#define GLOGGER_FILENAME "log.txt"
#define GLOGGER_LOG_PREFIX "LOG"
#define GLOGGER_ERROR_PREFIX "ERROR"

class GLogger {
    FILE * file = NULL;
public:
    inline GLogger(){
        file = fopen(GLOGGER_FILENAME, "w");

        if(file == NULL){
            throw "Nepodarilo sa otvorit lovaci subor " GLOGGER_FILENAME;
        }
    }
    inline ~GLogger(){
        fclose(file);
    }

    inline void error(std::string text){
        text = "[" GLOGGER_ERROR_PREFIX "] " + text;
        fwrite(text.c_str(), sizeof(char), text.size(), file);
    }

    inline void log(std::string text){
        text = "[" GLOGGER_ERROR_PREFIX "] " + text;
        fwrite(text.c_str(), sizeof(char), text.size(), file);
    }
};


#endif //GAMEENGINE_GLOGGER_H
