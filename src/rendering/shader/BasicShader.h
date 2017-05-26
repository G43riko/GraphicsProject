//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_BASICSHADER_H
#define GRAPHICSPROJECT_BASICSHADER_H

#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/utils/math/objects/Matrix4f.h>
#include <src/utils/resources/FileLoader.h>
#include <src/components/lights/SpotLight.h>
#include <src/components/lights/DirectionalLight.h>

#define MAX_LIGHTS 8
#define INFO_LENGTH 1024

#define KEYWORD_UNIFORM "uniform"
#define KEYWORD_SEMICOLUM ";"

class BasicShader{
private:
    std::map<std::string, int> uniforms;
    GLuint shader;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint geometryShader;
    const std::string vertexFileName;
    const std::string fragmentFileName;

    inline void addAllUniforms(const std::string content){
        long int uniformLocation = content.find(KEYWORD_UNIFORM, 0);
        while(uniformLocation != -1){
            long int begin = uniformLocation + sizeof(KEYWORD_UNIFORM);
            long int end = content.find(KEYWORD_SEMICOLUM, begin);
            std::string uniformLine = content.substr(begin, end - begin);
            std::string uniformName = uniformLine.substr(uniformLine.find(" "));
            uniformLocation = content.find(KEYWORD_UNIFORM, uniformLocation + sizeof(KEYWORD_UNIFORM));
        }
    }
//    inline void addAllUniforms(std::string content){
//        long int uniformLocation = content.find(KEYWORD_UNIFORM, 0);
//        while(uniformLocation != -1){
//            long int begin = uniformLocation + sizeof(KEYWORD_UNIFORM);
//            long int end = content.find(KEYWORD_SEMICOLUM, begin);
//            std::string uniformLine = content.substr(begin, end - begin);
//            std::string uniformName = uniformLine.substr(uniformLine.find(" "));
//            uniformLocation = content.find(KEYWORD_UNIFORM, uniformLocation + sizeof(KEYWORD_UNIFORM));
//        }
//    }
    inline int getUniformLocation(const std::string uniformName) const{
        return glGetUniformLocation(this -> shader, uniformName.c_str());
    }
    inline GLuint addShader(GLenum type, std::string fileName){
        GLint result = GL_FALSE;
        std::string fragment_shader_log(INFO_LENGTH, ' ');
        GLuint shader = glCreateShader(type);

        std::string content;

        ContentLoader::loadShader(fileName, &content);
//        if(fileName == "VoxelShader.frag"){
//            updateAllUniforms(content);
//        }
        const char * shaderContentPointer = content.c_str();

        //načíta obsah shadera
        glShaderSource(shader, 1, &shaderContentPointer, NULL);

        //skompiluje shadere
        glCompileShader(shader);

        //skontroluje či je skompilovaný
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE){
            glGetShaderInfoLog(shader, INFO_LENGTH, NULL, &fragment_shader_log[0]);
            ERROR(ERROR_COMPILE_SHADER(fileName, fragment_shader_log));
            return 0;
        }

        //vráti shader ak je uspešne skompilovaný
        return shader;
    }
public:
    inline BasicShader(const std::string vertex, const std::string fragment): vertexFileName(vertex), fragmentFileName(fragment){
        this -> shader = glCreateProgram();

        this -> vertexShader = this -> addShader(GL_VERTEX_SHADER, vertex + EXTENSION_VERTEX);
        //this -> geometryShader = this -> addShader(GL_GEOMETRY_SHADER, SHADERS_FOLDER + title + EXTENSION_GEOMETRY);
        this -> fragmentShader = this -> addShader(GL_FRAGMENT_SHADER, fragment + EXTENSION_FRAGMENT);

        glAttachShader(shader, vertexShader);
        glAttachShader(shader, fragmentShader);
    }

    inline BasicShader(const std::string shader) : BasicShader(shader, shader){};

    virtual ~BasicShader(void){
        cleanUp();
    }
    inline void cleanUp(void) const{
        if(this){
            glDeleteProgram(this -> shader);
            glDeleteShader(this -> vertexShader);
            glDeleteShader(this -> fragmentShader);
            //glDeleteShader(this -> geometryShader);
        }

    }

    inline void compileShader(void){
        glLinkProgram(this -> shader);
        glValidateProgram(this -> shader);
        this -> setAllAttributes();
        this -> setAllUniforms();
    }
    virtual void connectTextures(void){}

    inline void bind(void) const{
        glUseProgram(this -> shader);
    }

    inline void unbind(void) const{
        glUseProgram(0);
    }
    inline bool hasUniform(const std::string title) const{
        return uniforms.find(title) != uniforms.end();
    }

    inline void updateUniformi(const std::string& name, int value){
        glUniform1i(uniforms[name], value);
    }
    inline void updateUniformf(const std::string& name, float value){
        glUniform1f(uniforms[name], value);
    }
    inline void updateUniform2f(const std::string& name, const Vector2f& value){
        glUniform2f(uniforms[name], value.x, value.y);
    }
    inline void updateUniform4f(const std::string& name, const Vector4f& value){
        glUniform4f(uniforms[name], value.x, value.y, value.z, value.w);
    }
    inline void updateUniformb(const std::string& name, bool value){
        glUniform1i(uniforms[name], value ? 1 : 0);
    }
    inline void updateUniform4m(const std::string& name, const glm::mat4& matrix){
        glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, glm::value_ptr(matrix));
    }
    inline void updateUniform4m(const std::string& name, const Matrix4f& matrix){
        float * f = matrix.getArray();
        glUniformMatrix4fv(uniforms[name], 1, GL_FALSE, f);
        delete[] f;
    }
    inline void updateUniform3f(const std::string& name, float x, float y, float z){
        glUniform3f(uniforms[name], x, y, z);
    }
    inline void updateUniform3f(const std::string& name, const Vec3 & value){
        glUniform3f(uniforms[name], value.x, value.y, value.z);
    }
    inline void updateUniform3f(const std::string& name, const Vector3f & value){
        glUniform3f(uniforms[name], value.x, value.y, value.z);
    }
    inline void updateUniformNf(const std::string& name, const float * value, unsigned int size){
        glUniform1fv(uniforms[name], size, value);
    }

    inline void updateLight(const std::string& name, const LightData light){
        updateUniformi(name + ".type", light.type);
        updateUniform3f(name + ".position", light.position);
        updateUniform3f(name + ".diffuseColor", light.diffuseColor);
        updateUniform3f(name + ".specularColor", light.specularColor);
        updateUniform3f(name + ".attenuation", light.attenuation);
        updateUniform3f(name + ".direction", light.direction);
        updateUniformf(name + ".cutOff", light.cutOff);
        updateUniformf(name + ".outerCutOff", light.outerCutOff);
    }
    inline void updateDirLight(const std::string& name, const DirectionalLight light){
        updateUniformi(name + ".type", 1);
        updateUniform3f(name + ".direction", light.getDirection());
        updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
        updateUniform3f(name + ".specularColor", light.getSpecularColor());
    }
    inline void updatePointLight(const std::string& name, const PointLight light){
        updateUniformi(name + ".type", 2);
        updateUniform3f(name + ".position", light.getPosition());
        updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
        updateUniform3f(name + ".specularColor", light.getSpecularColor());
        updateUniform3f(name + ".attenuation", light.getAttenuation());
    }
    inline void updateSpotLight(const std::string& name, const SpotLight light){
        updateUniformi(name + ".type", 3);
        updateUniform3f(name + ".direction", light.getDirection());
        updateUniform3f(name + ".position", light.getPosition());
        updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
        updateUniform3f(name + ".attenuation", light.getAttenuation());
        updateUniformf(name + ".outerCutOff", light.getOuterCutOff());
        updateUniformf(name + ".cutOff", light.getCutOff());
    }
    inline void updateMaterial(const std::string& name, const MaterialData& mat){
        updateUniform3f(name + ".specularColor", mat.specularColor);
        updateUniform3f(name + ".ambientColor", mat.ambientColor);
        updateUniform3f(name + ".diffuseColor", mat.diffuseColor);
        updateUniformf(name + ".reflectivity", mat.reflectivity);
        updateUniformf(name + ".shineDumper", mat.shineDumper);
    }
protected:
    virtual void setAllAttributes(void) = 0;
    virtual void setAllUniforms(void) = 0;

    inline void bindAttribute(GLuint index, const char * title) const{
        glBindAttribLocation(shader, index, title);
    }
    inline void setUniform(const std::string& title){
        this -> uniforms[title] = this -> getUniformLocation(title.c_str());
    }
};


#endif //GRAPHICSPROJECT_BASICSHADER_H
