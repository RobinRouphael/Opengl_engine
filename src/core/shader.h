//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H


#include <opengl_stuff.h>
#include <string>
#include <iostream>
#include <cassert>
#include "material.h"


class Shader {

public:
    /**
     * Constructor
     * @param vertexShaderLocation
     * @param fragmentShaderLocation
     */
    Shader(const char*vertexShaderLocation, const char*fragmentShaderLocation);

    ~Shader();
    /**
     * Activate shaders
     */
    void use() const;
    /**
     * Add a PointLight
     * @param constant
     * @param linear
     * @param quadratic
     * @param pos
     * @param ambient
     * @param diffuse
     * @param specular
     */
    void addPointLight(GLfloat constant, GLfloat linear, GLfloat quadratic,
            const glm::vec3 & pos,const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
    /**
     * Add a SpotLight
     * @param dir
     * @param innerCutoff
     * @param outerCutoff
     * @param intensity
     * @param pos
     * @param ambient
     * @param diffuse
     * @param specular
     */
    void addSpotLight(const glm::vec3 &dir, GLfloat innerCutoff, GLfloat outerCutoff,GLfloat constant, GLfloat linear, GLfloat quadratic,
            GLfloat intensity, const glm::vec3 & pos,const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
    /**
     * Add a material
     * @param mat
     */
    void addMaterial(const Material &mat);
    /**
     * Reset lights in shaders
     */
    void clearLights();
    /**
     * The shader may need to know if the Model is textured
     * @param istextured
     */
    void isTextured(bool istextured);

    ///Uniform utils
    /**
     * Bool setter
     * @param name
     * @param value
     */
    void setBool(const std::string &name, bool value) const;
    /**
     * Int setter
     * @param name
     * @param value
     */
    void setInt(const std::string &name, int value) const;
    /**
     * Float setter
     * @param name
     * @param value
     */
    void setFloat(const std::string &name, float value) const;
    /**
     * Vec2 setter
     * @param name
     * @param value
     */
    void setVec2(const std::string &name, const glm::vec2 & value) const;
    /**
     * Vec3 setter
     * @param name
     * @param value
     */
    void setVec3(const std::string &name, const glm::vec3 & value) const;
    /**
     * Vec4 setter
     * @param name
     * @param value
     */
    void setVec4(const std::string &name, const glm::vec4 & value) const;
    /**
     * Mat2 setter
     * @param name
     * @param value
     */
    void setMat2(const std::string &name, const glm::mat2 & value) const;
    /**
     * Mat3 setter
     * @param name
     * @param value
     */
    void setMat3(const std::string &name, const glm::mat3 & value) const;
    /**
     * Mat4 setter
     * @param name
     * @param value
     */
    void setMat4(const std::string &name, const glm::mat4 & value) const;



private:

    GLint _success;
    GLchar _infoLog[512]; // warning fixed size ... request for LOG_LENGTH!!!
    GLuint _vertexshader, _fragmentshader;
    GLuint _program;
    GLuint nb_PointLight;
    GLuint nb_SpotLight;


};


#endif //ENGINE_SHADER_H
