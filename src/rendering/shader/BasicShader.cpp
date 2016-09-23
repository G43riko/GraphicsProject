//
// Created by gabriel on 22.9.2016.
//

#include "BasicShader.h"

BasicShader::BasicShader(const std::string title){
    this -> title = title;
    this -> shader = glCreateProgram();

    this -> vertexShader = addShader(GL_VERTEX_SHADER, title + EXTENSION_VERTEX);
    this -> geometryShader = addShader(GL_GEOMETRY_SHADER, title + EXTENSION_GEOMETRY);
    this -> fragmentShader = addShader(GL_FRAGMENT_SHADER, title + EXTENSION_FRAGMENT);

    glAttachShader(shader,vertexShader );
    glAttachShader(shader,fragmentShader );

    this -> setAllAttributes();
    glLinkProgram(shader);
    glValidateProgram(shader);
    this -> setAllUniforms();
};
BasicShader::~BasicShader(){
    glDeleteProgram(this -> shader);
    glDeleteShader(this -> vertexShader);
    glDeleteShader(this -> fragmentShader);
    glDeleteShader(this -> geometryShader);
};

GLuint BasicShader::addShader(int type, std::string fileName){
    unsigned int info_length = 1024;
    auto result = GL_FALSE;
    std::string fragment_shader_log(info_length, ' ');
    GLuint shader = glCreateShader(type);
    ContentLoader loader;
    auto shaderContentPointer = loader.loadFileContent(fileName).c_str();

    //načíta obsah shadera
    glShaderSource(shader, 1, &shaderContentPointer, nullptr);
    //skompiluje shadere
    glCompileShader(shader);

    //skontroluje či je skompilovaný
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        glGetShaderInfoLog(shader, info_length, nullptr, &fragment_shader_log[0]);
        Logger::error(ERROR_COMPILE_SHADER(fileName, fragment_shader_log));
        return 0;
    }

    //vráti shader ak je uspešne skompilovaný
    return shader;
}

int BasicShader::getUniformLocation(const std::string uniformName){
    return glGetUniformLocation(this -> shader, uniformName.c_str());
};

void BasicShader::connectTextures(){};
void BasicShader::bind(){
    glUseProgram(this -> shader);
};

void BasicShader::unbind(){
    glUseProgram(0);
};

void BasicShader::updateUniform(std::string name, int value){
    glUniform1i(uniforms[name], value);
};
void BasicShader::updateUniform(std::string name, float value){
    glUniform1f(uniforms[name], value);
};
void BasicShader::updateUniform(std::string name, Vector2f value){
    glUniform2f(uniforms[name], value.x, value.y);
};
void BasicShader::updateUniform(std::string name, Vector3f value){
    glUniform3f(uniforms[name], value.x, value.y, value.z);
};
void BasicShader::updateUniform(std::string name, Vector4f value){
    glUniform4f(uniforms[name], value.x, value.y, value.z, value.w);
};
void BasicShader::updateUniform(std::string name, bool value){
    glUniform1i(uniforms[name], value ? 1 : 0);
};
void BasicShader::bindAttribute(const int index, const char * title){
    //glBindAttribLocation(index, title);
};
void BasicShader::setUniform(std::string title){
    this -> uniforms[title] = this -> getUniformLocation(title.c_str());
};