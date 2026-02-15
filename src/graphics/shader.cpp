#include "shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <exception>

Shader::Shader()
{
}
bool Shader::loadCodeFromFiles(const std::string &vertexFile, const std::string &fragmentFile)
{
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexFile);
        fShaderFile.open(fragmentFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        _vShaderCode.clear();
        _fShaderCode.clear();

        _vShaderCode = vShaderStream.str();
        _fShaderCode = fShaderStream.str();
    }
    catch(std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            return false;
    }
    return true;
}
Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader){

    bool filesExist;
    try {
        filesExist = std::filesystem::exists(vertexShader) && std::filesystem::exists(fragmentShader);

    } catch (std::exception& e) {
        filesExist = false;
    }
    if(filesExist)
    {
        loadCodeFromFiles(vertexShader, fragmentShader);
    }
    else
    {
        _vShaderCode.clear();
        _fShaderCode.clear();

        _vShaderCode = vertexShader;
        _fShaderCode = fragmentShader;
    }
}
bool Shader::compile()
{
    return compileShader(this, _vShaderCode, _fShaderCode);
}
bool Shader::compileShader(Shader *dst, const std::string &vertexShader, const std::string &fragmentShader)
{
    const GLchar* vShaderCode = vertexShader.c_str();
    const GLchar* fShaderCode = fragmentShader.c_str();

    GLuint vertex, fragment;
    GLint success = 0;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
        std::cerr << infoLog << std::endl;
        return false;
    }

    if(success) {
        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
            std::cerr << infoLog << std::endl;
            return false;
        }
    }

    if(success) {
        // Shader Program
        GLuint programId = glCreateProgram();
        glAttachShader(programId, vertex);
        glAttachShader(programId, fragment);
        glLinkProgram(programId);
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(programId, 512, nullptr, infoLog);
            std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
            std::cerr << infoLog << std::endl;
            return false;
        }
        dst->_id = programId;
//        dst->_vShaderCode = vertexShader;
//        dst->_fShaderCode = fragmentShader;

    }
    dst->valid = bool(success);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}
