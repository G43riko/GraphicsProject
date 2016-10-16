//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_BASICSHADER_H
#define GRAPHICSPROJECT_BASICSHADER_H

#include <map>
#include <typeinfo>
#include <string>
#include "../../utils/Vectors.h"
#include "../../utils/Const.h"
#include "../../utils/FileLoader.h"
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class BasicShader{
    private:
        std::map<std::string, int> uniforms;
        GLuint shader;
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint geometryShader;
        std::string title;
        int getUniformLocation(const std::string uniformName);
        GLuint addShader(int, std::string);
    public:
        BasicShader(const std::string);
        ~BasicShader(void);
        static int MAX_LIGHTS;
        void connectTextures(void);
        void bind(void);
        void cleanUp();
        void unbind(void);
        void compileShader(void);
        void updateUniform(const std::string, const int);
        void updateUniform(const std::string, const float);
        void updateUniform(const std::string, const Vector2f);
        void updateUniform(const std::string, const Vector3f);
        void updateUniform(const std::string name, Vector3f * value){
            glUniform3f(uniforms[name], value -> x, value -> y, value -> z);
        }
        bool hasUniform(const std::string);
        void updateUniform(const std::string, const Vector4f);
        void updateUniform(const std::string, const bool);
        void updateUniform4m(const std::string, const glm::mat4);
    protected:
        virtual void setAllAttributes(void) = 0;
        virtual void setAllUniforms(void) = 0;
        void bindAttribute(const int index, const char * title);
        void setUniform(const std::string title);
};

typedef std::shared_ptr<BasicShader> PointerBasicShader;

#endif //GRAPHICSPROJECT_BASICSHADER_H
