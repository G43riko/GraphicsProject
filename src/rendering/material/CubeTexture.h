//
// Created by gabriel on 2.11.2016.
//

#ifndef GRAPHICSPROJECT_CUBETEXTURE_H
#define GRAPHICSPROJECT_CUBETEXTURE_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <memory>
#include <src/static_libs/lodepng.h>

class CubeTexture;

class CubeTexture {
    private:
        GLuint textureID;
        std::string title;
    public:
        CubeTexture(std::string title, GLuint textureID);
        GLuint getId(void);
        void cleanUp(void);
        void bind(void);
        void bind(GLuint num);
};


typedef std::shared_ptr<CubeTexture> PointerCubeTexture;
PointerCubeTexture createCubeTexture(std::string title, GLuint textureID);



#endif //GRAPHICSPROJECT_CUBETEXTURE_H
