//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_BASICSHADER_H
#define GRAPHICSPROJECT_BASICSHADER_H

#include <map>
#include <string>
#include "../../utils/Vectors.h"
#include "../../utils/FileLoader.h"
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/utils/Matrix4f.h>

class BasicShader{
    private:
        std::map<std::string, int> uniforms;
        GLuint shader;
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint geometryShader;
        std::string vertexFileName;
        std::string fragmentFileName;
        int getUniformLocation(const std::string uniformName);
        GLuint addShader(int, std::string);
    public:
        BasicShader(const std::string, const std::string);
        BasicShader(const std::string shader) : BasicShader(shader, shader){};
        ~BasicShader(void);
        static int MAX_LIGHTS;
        virtual void connectTextures(void);
        void bind(void);
        void cleanUp();
        void unbind(void);
        void compileShader(void);
        void updateUniformi(std::string, int);
        void updateUniformf(std::string, float);
        void updateUniform2f(std::string, const Vector2f &);

        void updateUniform3f(const std::string, const Vector3f &);

        bool hasUniform(const std::string);
        void updateUniform4f(std::string, const Vector4f &);
        void updateUniformb(std::string, bool);
        void updateUniform4m(const std::string, const glm::mat4);
        void updateUniform4m(const std::string, const Matrix4f);
    protected:
        virtual void setAllAttributes(void) = 0;
        virtual void setAllUniforms(void) = 0;
        void bindAttribute(const int index, const char * title);
        void setUniform(const std::string title);
};

typedef std::shared_ptr<BasicShader> PointerBasicShader;

#endif //GRAPHICSPROJECT_BASICSHADER_H
