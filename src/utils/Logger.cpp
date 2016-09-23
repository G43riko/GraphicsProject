//
// Created by gabriel on 22.9.2016.
//
#include <iostream>

#ifndef GRAPHICSPROJECT_LOGGER_B
#define GRAPHICSPROJECT_LOGGER_B

class Logger{
    public:
        static void write(const std::string message){
            std::cout << message << std::endl;
        }
        static void write(const char * message){
            std::cout << message << std::endl;
        }
        static void error(const char * message){
            std::cerr << message << std::endl;
        }
        static void error(const std::string  message){
            std::cerr << message << std::endl;
        }
};

#endif