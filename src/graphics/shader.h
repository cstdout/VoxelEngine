#ifndef GRAPHICS_SHADER_H_
#define GRAPHICS_SHADER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader {
public:
    Shader();
    Shader(const std::string& vertexShader, const std::string& fragmentShader);
    ~Shader();

    bool loadCodeFromFiles(const std::string& vertexFile, const std::string& fragmentFile);
    bool compile();
    void use();
    static Shader* compileFromFiles(const std::string& vertexFile, const std::string& fragmentFile);
    bool isValid();

    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
    void setUniform1i(const std::string& name, uint32_t v) const;
    void setUniformMatrix4fv(const std::string& name, const GLfloat* value, GLsizei count = 1, GLboolean transpose = false) const;


    void setBool(const std::string &name, bool value) const;
    void setUniform1f(const std::string &name, float value) const;

    void setUniform2fv(const std::string &name, const GLfloat* value) const;
    void setUniform2f(const std::string &name, float x, float y) const;

    void setUniform3fv(const std::string &name, const GLfloat* value) const;

    void setUniform3f(const std::string &name, float x, float y, float z) const;

    void setUniform4fv(const std::string &name, const GLfloat* value) const;

    void setUniformMatrix2fv(const std::string &name, const GLfloat* mat) const;

    void setUniformMatrix3fv(const std::string &name, const GLfloat* mat) const;

    void setUniformArrayFloat(const std::string& name, const float* arr, uint32_t size) const;
    void setUniformArrayVec4(const std::string& name, const float** arr, uint32_t size) const;
    void setUniformArrayVec2(const std::string& name, const float** arr, uint32_t size) const;

    int32_t getUniformLocation(const std::string& name) const;
    int32_t getAttribLocation(const std::string& name) const;

    uint32_t id() const;

    int32_t getUniformCount() const;


private:
    uint32_t _id;
    bool valid = false;
    std::string _vShaderCode;
    std::string _fShaderCode;
    static bool compileShader(Shader* dst, const std::string& vertexShader, const std::string& fragmentShader);

};



#endif /* GRAPHICS_SHADER_H_ */
