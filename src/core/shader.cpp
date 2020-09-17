//
// Created by Robin on 22/02/2020.
//


#include <sstream>
#include <fstream>
#include "shader.h"

Shader::Shader(const char* vertexShaderSource, const char*fragmentShaderSource):
    nb_PointLight{0},
    nb_SpotLight{0}
{

    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexShaderSource);
        fShaderFile.open(fragmentShaderSource);

        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string

    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 1. Generate the shader
    _vertexshader = glCreateShader(GL_VERTEX_SHADER);
    // 2. set the source
    glShaderSource(_vertexshader, 1, &vShaderCode , NULL);
    // 3. Compile
    glCompileShader(_vertexshader);
    // 4. test for compile error
    glGetShaderiv(_vertexshader, GL_COMPILE_STATUS, &_success);
    if(!_success) {
        glGetShaderInfoLog(_vertexshader, 512, NULL, _infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog << std::endl;
    }

    _fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragmentshader, 1, &fShaderCode, NULL);
    glCompileShader(_fragmentshader);
    glGetShaderiv(_fragmentshader, GL_COMPILE_STATUS, &_success);
    if(!_success) {
        glGetShaderInfoLog(_fragmentshader, 512, NULL, _infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << _infoLog << std::endl;
    }
    // 1. Generate the program
    _program = glCreateProgram();
    // 2. Attach the shaders to the program
    glAttachShader(_program, _vertexshader);
    glAttachShader(_program, _fragmentshader);
    // 3. Link the program
    glLinkProgram(_program);
    // 4. Test for link errors
    glGetProgramiv(_program, GL_LINK_STATUS, &_success);
    if(!_success) {
        glGetProgramInfoLog(_program, 512, NULL, _infoLog);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n" << _infoLog << std::endl;
    }
    glDeleteShader(_vertexshader);
    glDeleteShader(_fragmentshader);
}

Shader::~Shader()
{

}

void Shader::use() const
{
    glUseProgram(_program);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(_program, name.c_str()), (GLuint)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 & value) const
{
    glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 & value) const
{
    glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, const glm::vec4 & value) const
{
    glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat2(const std::string &name, const glm::mat2 & value) const
{
    glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat3(const std::string &name, const glm::mat3 & value) const
{
    glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, const glm::mat4 & value) const
{
    glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::addPointLight(GLfloat constant, GLfloat linear, GLfloat quadratic,const glm::vec3 &pos, const glm::vec3 &ambient,
                           const glm::vec3 &diffuse, const glm::vec3 &specular)
{
    setVec3("point_light[" + std::to_string(nb_PointLight) +"].ambient", ambient);
    setVec3("point_light[" + std::to_string(nb_PointLight) +"].diffuse", diffuse);
    setVec3("point_light[" + std::to_string(nb_PointLight) +"].specular", specular);
    setVec3("point_light[" + std::to_string(nb_PointLight) + "].position", pos);
    setFloat("point_light[" + std::to_string(nb_PointLight) + "].constant", constant);
    setFloat("point_light[" + std::to_string(nb_PointLight) + "].linear", linear);
    setFloat("point_light[" + std::to_string(nb_PointLight) + "].quadratic", quadratic);
    setInt("nb_pointLight", ++nb_PointLight);
}

void Shader::addMaterial(const Material &mat)
{
    setInt("mat.diffuse",0); //texture
    setInt("mat.specular",1); //texture
    setFloat("mat.shininess",32.f);
    /*setVec3("mat.albedo", mat.albedo());
    setFloat("mat.metalness", mat.metalness());
    setFloat("mat.roughness", mat.roughness());
    setFloat("mat.ao", mat.ambientOcclusion());*/
}

void Shader::clearLights()
{
    nb_PointLight =0;
    nb_SpotLight =0;
    setInt("nb_pointLight", 0);
    setInt("nb_spotLight", 0);
}

void Shader::isTextured(bool istextured)
{
    setBool("objectIsTextured",istextured);
}

void Shader::addSpotLight(const glm::vec3 &dir, GLfloat innerCutoff, GLfloat outerCutoff, GLfloat constant, GLfloat linear, GLfloat quadratic,GLfloat intensity,
                          const glm::vec3 &pos, const glm::vec3 &ambient, const glm::vec3 &diffuse,
                          const glm::vec3 &specular)
{
    setVec3("spot_light[" + std::to_string(nb_SpotLight) +"].ambient", ambient);
    setVec3("spot_light[" + std::to_string(nb_SpotLight) +"].diffuse", diffuse);
    setVec3("spot_light[" + std::to_string(nb_SpotLight) +"].specular", specular);
    setVec3("spot_light[" + std::to_string(nb_SpotLight) + "].position", pos);
    setVec3("spot_light[" + std::to_string(nb_SpotLight) + "].direction", dir);
    setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].cutOff", innerCutoff);
    setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].outerCutOff", outerCutoff);
    //setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].intensity", intensity);
    setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].constant", constant);
    setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].linear", linear);
    setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].quadratic", quadratic);
    setInt("nb_spotLight", ++nb_SpotLight);

}




