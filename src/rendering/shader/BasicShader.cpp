//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_BASICSHADER_H

#include "BasicShader.h"


BasicShader::BasicShader(const std::string vertex, const std::string fragment){
    this -> vertexFileName = vertex;
    this -> fragmentFileName = fragment;
    this -> shader = glCreateProgram();

    this -> vertexShader = this -> addShader(GL_VERTEX_SHADER, "res/shaders/" + vertex + EXTENSION_VERTEX);
    //this -> geometryShader = this -> addShader(GL_GEOMETRY_SHADER, "src/shaders/" + title + EXTENSION_GEOMETRY);
    this -> fragmentShader = this -> addShader(GL_FRAGMENT_SHADER, "res/shaders/" + fragment + EXTENSION_FRAGMENT);

    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
}
BasicShader::~BasicShader(void){
    cleanUp();
}

void BasicShader::cleanUp(){
    if(this){
        glDeleteProgram(this -> shader);
        glDeleteShader(this -> vertexShader);
        glDeleteShader(this -> fragmentShader);
        //glDeleteShader(this -> geometryShader);
    }

}

void BasicShader::compileShader(){
    glLinkProgram(this -> shader);
    glValidateProgram(this -> shader);
    this -> setAllAttributes();
    this -> setAllUniforms();
}

GLuint BasicShader::addShader(GLenum type, std::string fileName){
    unsigned int info_length = 1024;
    GLint result = GL_FALSE;
    std::string fragment_shader_log(info_length, ' ');
    GLuint shader = glCreateShader(type);

    std::string content;

    ContentLoader::loadTextFile(fileName, &content);

    const char * shaderContentPointer = content.c_str();

    //načíta obsah shadera
    glShaderSource(shader, 1, &shaderContentPointer, NULL);

    //skompiluje shadere
    glCompileShader(shader);

    //skontroluje či je skompilovaný
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        glGetShaderInfoLog(shader, info_length, NULL, &fragment_shader_log[0]);
        ERROR(ERROR_COMPILE_SHADER(fileName, fragment_shader_log));
        return 0;
    }

    //vráti shader ak je uspešne skompilovaný
    return shader;
}

int BasicShader::getUniformLocation(const std::string uniformName){
    return glGetUniformLocation(this -> shader, uniformName.c_str());
}

void BasicShader::connectTextures(){}
void BasicShader::bind(){
    glUseProgram(this -> shader);
}

void BasicShader::unbind(){
    glUseProgram(0);
}
bool BasicShader::hasUniform(const std::string title){
    return uniforms.find(title) != uniforms.end();
}


void BasicShader::bindAttribute(const int index, const char * title){
    glBindAttribLocation(shader, index, title);
}
void BasicShader::setUniform(std::string title){
    this -> uniforms[title] = this -> getUniformLocation(title.c_str());
}

void BasicShader::updateUniformi(std::string name, int value){
    glUniform1i(uniforms[name], value);
}
void BasicShader::updateUniformf(std::string name, float value){
    glUniform1f(uniforms[name], value);
}
void BasicShader::updateUniform2f(std::string name, const Vector2f &value){
    glUniform2f(uniforms[name], value.x, value.y);
}
void BasicShader::updateUniform4f(std::string name, const Vector4f &value){
    glUniform4f(uniforms[name], value.x, value.y, value.z, value.w);
}
void BasicShader::updateUniformb(std::string name, bool value){
    glUniform1i(uniforms[name], value ? 1 : 0);
}
void BasicShader::updateUniform4m(const std::string name, const glm::mat4 matrix){
    glUniformMatrix4fv(uniforms[name], 1, false, glm::value_ptr(matrix));
}
void BasicShader::updateUniform4m(const std::string name, const Matrix4f matrix){
    float * f = matrix.getArray();
    glUniformMatrix4fv(uniforms[name], 1, false, f);
    delete[] f;
}

void BasicShader::updateUniform3f(const std::string name, const Vector3f & value){
    glUniform3f(uniforms[name], value.x, value.y, value.z);
}


void BasicShader::updateDirLight(const std::string name, DirectionalLight light){
    updateUniformi(name + ".type", 1);
    updateUniform3f(name + ".direction", light.getDirection());
    updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
    updateUniform3f(name + ".specularColor", light.getSpecularColor());
}
void BasicShader::updatePointLight(const std::string name, PointLight light){
    updateUniformi(name + ".type", 2);
    updateUniform3f(name + ".position", light.getPosition());
    updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
    updateUniform3f(name + ".specularColor", light.getSpecularColor());
    updateUniform3f(name + ".attenuation", light.getAttenuation());
}
void BasicShader::updateSpotLight(const std::string name, SpotLight light){
    updateUniformi(name + ".type", 3);
    updateUniform3f(name + ".direction", light.getDirection());
    updateUniform3f(name + ".position", light.getPosition());
    updateUniform3f(name + ".diffuseColor", light.getDiffuseColor());
    updateUniform3f(name + ".attenuation", light.getAttenuation());
    updateUniformf(name + ".outerCutOff", light.getOuterCutOff());
    updateUniformf(name + ".cutOff", light.getCutOff());
}

#endif