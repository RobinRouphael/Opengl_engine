//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H


#include <opengl_stuff.h>
#include <string>
#include <iostream>
#include <cassert>


class Shader {

public:
    /**
     * Constructor
     * @param tp_vertexShaderLocation
     * @param tp_fragmentShaderLocation
     */
    Shader(const char *tp_vertexShaderLocation, const char * tp_fragmentShaderLocation);

    ~Shader();
    /**
     * Activate shaders
     */
    void use() const;

    ///Uniform utils
    /**
     * Bool setter
     * @param tr_name
     * @param t_value
     */
    void setBool(const std::string &tr_name, bool t_value) const;
    /**
     * Int setter
     * @param tr_name
     * @param t_value
     */
    void setInt(const std::string &tr_name, int t_value) const;
    /**
     * Float setter
     * @param tr_name
     * @param t_value
     */
    void setFloat(const std::string &tr_name, float t_value) const;
    /**
     * Vec2 setter
     * @param tr_name
     * @param t_value
     */
    void setVec2(const std::string &tr_name, const glm::vec2 & t_value) const;
    /**
     * Vec3 setter
     * @param tr_name
     * @param t_value
     */
    void setVec3(const std::string &tr_name, const glm::vec3 & t_value) const;
    /**
     * Vec4 setter
     * @param tr_name
     * @param t_value
     */
    void setVec4(const std::string &tr_name, const glm::vec4 & t_value) const;
    /**
     * Mat2 setter
     * @param tr_name
     * @param t_value
     */
    void setMat2(const std::string &tr_name, const glm::mat2 & t_value) const;
    /**
     * Mat3 setter
     * @param tr_name
     * @param t_value
     */
    void setMat3(const std::string &tr_name, const glm::mat3 & t_value) const;
    /**
     * Mat4 setter
     * @param tr_name
     * @param t_value
     */
    void setMat4(const std::string &tr_name, const glm::mat4 & t_value) const;



private:

    GLint m_success;
    GLchar m_info_log[512]; // warning fixed size ... request for LOG_LENGTH!!!
    GLuint m_vertexshader, m_fragmentshader;
    GLuint m_program;


};


#endif //ENGINE_SHADER_H
