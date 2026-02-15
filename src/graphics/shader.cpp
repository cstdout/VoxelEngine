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
