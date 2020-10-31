//
// Created by Robin on 10/03/2020.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H



#include <opengl_stuff.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material {
public:
    Material() :
            m_albedo {0.5f, 0.0f, 0.0f}
    , m_metalness {0.8f}
    , m_roughness {0.2f}
    , m_ao {0.5f} {}

    Material(const glm::vec3 &tr_albedo, float t_metalness, float t_roughness, float t_ao):
            m_albedo {tr_albedo}
            , m_metalness {t_metalness}
            , m_roughness {t_roughness}
            , m_ao {t_ao} {}


    const glm::vec3 &albedo() const {
        return m_albedo;
    }

    float metalness() const {
        return m_metalness;
    }
    float roughness() const {
        return m_roughness;
    }
    float ambientOcclusion() const {
        return m_ao;
    }

private:
    glm::vec3 m_albedo;
    float m_metalness;
    float m_roughness;
    float m_ao;
};


#endif //ENGINE_MATERIAL_H
