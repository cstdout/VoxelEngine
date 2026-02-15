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
Shader* Shader::compileFromFiles(const std::string &vertexFile, const std::string &fragmentFile)
{

    Shader* shader = new Shader;
    bool res = shader->loadCodeFromFiles(vertexFile, fragmentFile);
    if (res)
    {
        res = shader->compile();
    }
    if(res)
    {
        return shader;
    }
    return nullptr;
}
void Shader::use(){
    if (valid) {
        glUseProgram(_id);
    }
    else
    {
        std::cerr << "ERROR::SHADER::IS NOT VALID" << std::endl;
    }
}
bool Shader::isValid()
{
    return valid;
}
uint32_t Shader::id() const
{
    return _id;
}
int32_t Shader::getUniformCount() const
{
    int32_t count = -1;
    if(valid)
    {
        glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &count);
    }

    return count;
}
int32_t Shader::getUniformLocation(const std::string& name) const
{
    int32_t location = glGetUniformLocation(_id, name.c_str());
    if (location < 0)
    {
        std::cerr << "ERROR::SHADER::CANNOT FIND UNIFORM LOCATION OF " << name.c_str() << std::endl;
    }
    return location;
}
int32_t Shader::getAttribLocation(const std::string& name) const
{
    return glGetAttribLocation(_id, name.c_str());
}
void Shader::setUniformMatrix4fv(const std::string& name, const GLfloat* value, GLsizei count, GLboolean transpose) const
{
    glUniformMatrix4fv(getUniformLocation(name), count, transpose, value);
}
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(getUniformLocation(name), (int)value);
}
void Shader::setUniform1f(const std::string &name, float value) const
{
    glUniform1f(getUniformLocation(name), value);
}
void Shader::setUniform2fv(const std::string &name, const GLfloat* value) const
{
    glUniform2fv(getUniformLocation(name), 1, value);
}
void Shader::setUniform2f(const std::string &name, float x, float y) const
{
    glUniform2f(getUniformLocation(name), x, y);
}
void Shader::setUniform3fv(const std::string &name, const GLfloat* value) const
{
    glUniform3fv(getUniformLocation(name), 1, value);
}
void Shader::setUniform3f(const std::string &name, float x, float y, float z) const
{
    glUniform3f(getUniformLocation(name), x, y, z);
}
void Shader::setUniform4fv(const std::string &name, const GLfloat* value) const
{
    glUniform4fv(getUniformLocation(name), 1, value);
}
void Shader::setUniformMatrix2fv(const std::string &name, const GLfloat* mat) const
{
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, mat);
}
void Shader::setUniformMatrix3fv(const std::string &name, const GLfloat* mat) const
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, mat);
}
void Shader::setUniformArrayFloat(const std::string& name, const float* arr, uint32_t size) const
{
    for(uint32_t i = 0; i < size; ++i)
    {
        glUniform1f(getUniformLocation(name + "[" + std::to_string(i) + "]"), arr[i]);
    }
}
void Shader::setUniformArrayVec4(const std::string& name, const float** arr, uint32_t size) const
{
    for(uint32_t i = 0; i < size; ++i)
    {
        glUniform4fv(getUniformLocation(name + "[" + std::to_string(i) + "]"), 1, arr[i]);
    }
}
void Shader::setUniformArrayVec2(const std::string& name, const float** arr, uint32_t size) const
{
    for(uint32_t i = 0; i < size; ++i)
    {
        glUniform2fv(getUniformLocation(name + "[" + std::to_string(i) + "]"), 1, arr[i]);
    }
}
