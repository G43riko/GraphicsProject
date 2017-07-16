//
// Created by gabriel on 1.7.2017.
//

#ifndef GAMEENGINE_GCONSOLE_H
#define GAMEENGINE_GCONSOLE_H

#include <string>
#include <iostream>

#define PRINT_LINE_MSG(x) (GCons::printLine(__LINE__, __FILE__, x))
#define PRINT_LINE() (GCons::printLine(__LINE__, __FILE__))

namespace GCons{
    enum Code {
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

    constexpr std::string LOG_PREFIX = "INFO";
    constexpr std::string ERROR_PREFIX = "ERROR";
    constexpr Modifier DEFAULT_COLOR(FG_DEFAULT);

    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream & operator << (std::ostream &os, const Modifier &mod) {
            return os << "\033[" << mod.code << "m";
        }
    };

    constexpr void printLine (int line, const std::string& file , std::string message = ""){
        if(!message.empty()){
            message = "-> " + message;
        }
        printf("%s:%d %s\n", file.c_str(), line, message.c_str());
    };

    constexpr void printColor(const std::string& msg, Code color){
        std::cout << Modifier(color) << msg << DEFAULT_COLOR << std::endl;
    };

    constexpr void printError(const std::string& msg){
        printColor(ERROR_PREFIX + " " + msg, FG_RED);
    };

}

#endif //GAMEENGINE_GCONSOLE_H
