//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_BASICSHADER_H
#define GRAPHICSPROJECT_BASICSHADER_H

#include <map>
#include <string>
#include "../../utils/Vectors.h"
#include "../../utils/Const.h"
#include "../../utils/ContentLoader.h"
#include <GL/glew.h>

class BasicShader{
    private:
        std::map<std::string, int> uniforms;
        GLuint shader = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLuint geometryShader = 0;
        std::string title;
        int getUniformLocation(const std::string uniformName);
        GLuint addShader(int, std::string);
    public:
        BasicShader(const std::string);
        ~BasicShader();
        void connectTextures(void );
        void bind(void);
        void unbind(void);

        void updateUniform(const std::string, const int);
        void updateUniform(const std::string, const float);
        void updateUniform(const std::string, const Vector2f);
        void updateUniform(const std::string, const Vector3f);
        void updateUniform(const std::string, const Vector4f);
        void updateUniform(const std::string, const bool);
    protected:
        virtual void setAllAttributes(void) = 0;
        virtual void setAllUniforms(void ) = 0;
        void bindAttribute(const int index, const char * title);
        void setUniform(const std::string title);
};


#endif //GRAPHICSPROJECT_BASICSHADER_H
