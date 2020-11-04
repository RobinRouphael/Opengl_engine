//
// Created by Robin on 22/02/2020.
//


#include <sstream>
#include <fstream>
#include "shader.h"

Shader::Shader(const char* tp_vertexShaderLocation, const char*tp_fragmentShaderLocation):
        m_nb_point_light{0},
        m_nb_spot_light{0}
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
        vShaderFile.open(tp_vertexShaderLocation);
        fShaderFile.open(tp_fragmentShaderLocation);

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
    m_vertexshader = glCreateShader(GL_VERTEX_SHADER);
    // 2. set the source
    glShaderSource(m_vertexshader, 1, &vShaderCode , NULL);
    // 3. Compile
    glCompileShader(m_vertexshader);
    // 4. test for compile error
    glGetShaderiv(m_vertexshader, GL_COMPILE_STATUS, &m_success);
    if(!m_success) {
        glGetShaderInfoLog(m_vertexshader, 512, NULL, m_info_log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << m_info_log << std::endl;
    }

    m_fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentshader, 1, &fShaderCode, NULL);
    glCompileShader(m_fragmentshader);
    glGetShaderiv(m_fragmentshader, GL_COMPILE_STATUS, &m_success);
    if(!m_success) {
        glGetShaderInfoLog(m_fragmentshader, 512, NULL, m_info_log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << m_info_log << std::endl;
    }
    // 1. Generate the program
    m_program = glCreateProgram();
    // 2. Attach the shaders to the program
    glAttachShader(m_program, m_vertexshader);
    glAttachShader(m_program, m_fragmentshader);
    // 3. Link the program
    glLinkProgram(m_program);
    // 4. Test for link errors
    glGetProgramiv(m_program, GL_LINK_STATUS, &m_success);
    if(!m_success) {
        glGetProgramInfoLog(m_program, 512, NULL, m_info_log);
        std::cerr << "ERROR::SHADER::LINK_FAILED\n" << m_info_log << std::endl;
    }
    glDeleteShader(m_vertexshader);
    glDeleteShader(m_fragmentshader);
}

Shader::~Shader()
{

}

void Shader::use() const
{
    glUseProgram(m_program);
}

void Shader::setBool(const std::string &tr_name, bool t_value) const
{
    glUniform1i(glGetUniformLocation(m_program, tr_name.c_str()), (GLuint)t_value);
}

void Shader::setInt(const std::string &tr_name, int t_value) const
{
    glUniform1i(glGetUniformLocation(m_program, tr_name.c_str()), t_value);
}

void Shader::setFloat(const std::string &tr_name, float t_value) const
{
    glUniform1f(glGetUniformLocation(m_program, tr_name.c_str()), t_value);
}

void Shader::setVec2(const std::string &tr_name, const glm::vec2 & t_value) const
{
    glUniform2fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, glm::value_ptr(t_value));
}

void Shader::setVec3(const std::string &tr_name, const glm::vec3 & t_value) const
{
    glUniform3fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, glm::value_ptr(t_value));
}

void Shader::setVec4(const std::string &tr_name, const glm::vec4 & t_value) const
{
    glUniform4fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, glm::value_ptr(t_value));
}

void Shader::setMat2(const std::string &tr_name, const glm::mat2 & t_value) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, GL_FALSE, glm::value_ptr(t_value));
}

void Shader::setMat3(const std::string &tr_name, const glm::mat3 & t_value) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, GL_FALSE, glm::value_ptr(t_value));
}

void Shader::setMat4(const std::string &tr_name, const glm::mat4 & t_value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, tr_name.c_str()), 1, GL_FALSE, glm::value_ptr(t_value));
}



void Shader::clearLights()
{
    m_nb_point_light =0;
    m_nb_spot_light =0;
    setInt("nb_pointLight", 0);
    setInt("nb_spotLight", 0);
}

void Shader::isTextured(bool t_istextured)
{
    setBool("objectIsTextured", t_istextured);
}

void Shader::addSpotLight(const glm::vec3 &tr_dir, GLfloat t_innerCutoff, GLfloat t_outerCutoff, GLfloat t_constant, GLfloat t_linear, GLfloat t_quadratic, GLfloat t_intensity,
                          const glm::vec3 &tr_pos, const glm::vec3 &tr_ambient, const glm::vec3 &tr_diffuse,
                          const glm::vec3 &tr_specular)
{
    setVec3("spot_light[" + std::to_string(m_nb_spot_light) + "].ambient", tr_ambient);
    setVec3("spot_light[" + std::to_string(m_nb_spot_light) + "].diffuse", tr_diffuse);
    setVec3("spot_light[" + std::to_string(m_nb_spot_light) + "].specular", tr_specular);
    setVec3("spot_light[" + std::to_string(m_nb_spot_light) + "].position", tr_pos);
    setVec3("spot_light[" + std::to_string(m_nb_spot_light) + "].direction", tr_dir);
    setFloat("spot_light[" + std::to_string(m_nb_spot_light) + "].cutOff", t_innerCutoff);
    setFloat("spot_light[" + std::to_string(m_nb_spot_light) + "].outerCutOff", t_outerCutoff);
    //setFloat("spot_light[" + std::to_string(nb_SpotLight) + "].intensity", intensity);
    setFloat("spot_light[" + std::to_string(m_nb_spot_light) + "].constant", t_constant);
    setFloat("spot_light[" + std::to_string(m_nb_spot_light) + "].linear", t_linear);
    setFloat("spot_light[" + std::to_string(m_nb_spot_light) + "].quadratic", t_quadratic);
    setInt("nb_spotLight", ++m_nb_spot_light);

}




