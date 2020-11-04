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
    /**
     * Add a PointLight
     * @param t_constant
     * @param t_linear
     * @param t_quadratic
     * @param tr_pos
     * @param tr_ambient
     * @param tr_diffuse
     * @param tr_specular
     */

    void addSpotLight(const glm::vec3 &tr_dir, GLfloat t_innerCutoff, GLfloat t_outerCutoff, GLfloat t_constant, GLfloat t_linear, GLfloat t_quadratic,
                      GLfloat t_intensity, const glm::vec3 & tr_pos, const glm::vec3 &tr_ambient, const glm::vec3 &tr_diffuse, const glm::vec3 &tr_specular);

    /**
     * Reset lights in shaders
     */
    void clearLights();
    /**
     * The shader may need to know if the Model is textured
     * @param t_istextured
     */
    void isTextured(bool t_istextured);

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
    GLuint m_nb_point_light;
    GLuint m_nb_spot_light;


};


#endif //ENGINE_SHADER_H
