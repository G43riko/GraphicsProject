//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_PPM_H
#define GAMEENGINE_PPM_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

class PPM {
    inline void init(void){
        width = 0;
        height = 0;
        max_col_val = 255;
    };
    //info about the PPM file (height and width)
    uint nr_lines;
    uint nr_columns;

public:
    //arrays for storing the R,G,B values
    std::vector<u_char> r;
    std::vector<u_char> g;
    std::vector<u_char> b;
    //
    uint height;
    uint width;
    uint max_col_val;
    //total number of elements (pixels)
    uint size;

    inline PPM(void){
        init();
    };
    //create a PPM object and fill it with data stored in fname
    inline PPM(const std::string &fname){
        init();
        read(fname);
    };

    //create an "epmty" PPM image with a given width and height;the R,G,B arrays are filled with zeros
    inline PPM(const uint _width, const uint _height){
        init();
        width = _width;
        height = _height;
        nr_lines = height;
        nr_columns = width;
        size = width * height;

        // fill r, g and b with 0
        r.resize(size);
        g.resize(size);
        b.resize(size);
    };
    //read the PPM image from fname
    inline void read(const std::string &fname){
        std::ifstream inp(fname.c_str(), std::ios::in | std::ios::binary);
        if (inp.is_open()) {
            std::string line;
            std::getline(inp, line);
            if (line != "P6") {
                std::cout << "Error. Unrecognized file format." << std::endl;
                return;
            }
            std::getline(inp, line);
            while (line[0] == '#') {
                std::getline(inp, line);
            }
            std::stringstream dimensions(line);

            try {
                dimensions >> width;
                dimensions >> height;
                nr_lines = height;
                nr_columns = width;
            } catch (std::exception &e) {
                std::cout << "Header file format error. " << e.what() << std::endl;
                return;
            }

            std::getline(inp, line);
            std::stringstream max_val(line);
            try {
                max_val >> max_col_val;
            } catch (std::exception &e) {
                std::cout << "Header file format error. " << e.what() << std::endl;
                return;
            }

            size = width * height;

            r.reserve(size);
            g.reserve(size);
            b.reserve(size);

            char aux;
            for (uint i = 0; i < size; ++i) {
                inp.read(&aux, 1);
                r[i] = (u_char) aux;
                inp.read(&aux, 1);
                g[i] = (u_char) aux;
                inp.read(&aux, 1);
                b[i] = (u_char) aux;
            }
        } else {
            std::cout << "Error. Unable to open " << fname << std::endl;
        }
        inp.close();
    };
    //write the PPM image in fname
    inline void write(const std::string &fname) const{
        std::ofstream inp(fname.c_str(), std::ios::out | std::ios::binary);
        if (inp.is_open()) {

            inp << "P6\n";
            inp << width;
            inp << " ";
            inp << height << "\n";
            inp << max_col_val << "\n";

            char aux;
            for (uint i = 0; i < size; ++i) {
                aux = (char) r[i];
                inp.write(&aux, 1);
                aux = (char) g[i];
                inp.write(&aux, 1);
                aux = (char) b[i];
                inp.write(&aux, 1);
            }
        } else {
            std::cout << "Error. Unable to open " << fname << std::endl;
        }
        inp.close();
    };
};


#endif //GAMEENGINE_PPM_H
