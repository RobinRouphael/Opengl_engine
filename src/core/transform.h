//
// Created by robin on 24/12/2020.
//

#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H


#include "geometry.h"

class Transform {
public:




    Transform(glm::vec3 t_scale = glm::vec3(1), glm::vec3 t_translation = glm::vec3(0), glm::vec3 t_rotation = glm::vec3(0)):
    m_scale(t_scale),
    m_rotation(t_rotation),
    m_translation(t_translation)
    {}
    /**
     * Get Model Matrix
     * @return Translation Mat * Rotation Mat * Scale Mat
     */
    [[nodiscard]] glm::mat4 getTransform() const{
        return glm::translate(glm::mat4(), m_translation)
               * getRotationMatrix()
               *glm::scale(glm::mat4(), m_scale);
    }
    /**
     * Scale getter
     * @return scale vector
     */
    glm::vec3 getScale(){return m_scale;}
    /**
     * Scale setter
     * @param t_scale vector
     */
    void setScale(glm::vec3 t_scale){ m_scale = t_scale;}
    /**
     * Rotation getter
     * @return rotation vector
     */
    glm::vec3 getRotation(){return m_rotation;}
    /**
     * Rotation setter
     * @param t_rotation vector
     */
    void setRotation(glm::vec3 t_rotation){ m_rotation = t_rotation;}
    /**
     * Position getter
     * @return position vector
     */
    glm::vec3 getTranslation(){return m_translation;}
    /**
     * Position setter
     * @param t_position vector
     */
    void setTranslation(glm::vec3 t_position){ m_translation = t_position;}

private:

    glm::vec3 m_scale;
    glm::vec3 m_translation;
    glm::vec3 m_rotation;
private:
    /**
     * Get Rotation Matrix
     * @return Rotation Matrix
     */
    [[nodiscard]] glm::mat4 getRotationMatrix() const{
        glm::vec3 x{1.f, 0.f, 0.f};
        glm::vec3 y{0.f, 1.f, 0.f};
        glm::vec3 z{0.f, 0.f, 1.f};
        glm::mat4 rot = glm::rotate(glm::mat4(), glm::radians(m_rotation.x), x);
        rot = glm::rotate(rot, glm::radians(m_rotation.y), y);
        rot = glm::rotate(rot, glm::radians(m_rotation.z), z);
        return rot;
    }


protected:


};


#endif //ENGINE_TRANSFORM_H
