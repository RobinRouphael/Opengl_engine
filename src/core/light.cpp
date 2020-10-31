//
// Created by Robin on 26/02/2020.
//

#include <src/models/cube.h>
#include "light.h"

Light::Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const std::shared_ptr<Model> &t_representation):
        m_ambient{t_ambient},
        m_diffuse{t_diffuse},
        m_specular{t_specular},
        m_representation(t_representation)
{

}

Light::~Light()
{

}

void Light::addToShader(Shader &t_shader)
{

}

void Light::drawLight(Shader &t_shader)
{
    m_representation->drawModel(t_shader, GL_TRIANGLES);
}


PointLight::~PointLight(){}

PointLight::PointLight():
        Light(glm::vec3(0.5f),glm::vec3(2.f),glm::vec3(1.f),std::make_shared<Cube>()),
        m_constant{1.f},
        m_linear{0.99f},
        m_quadratic{0.032f}

{
    m_representation->setTranslation(glm::vec3(0.7f, 0.2f, 2.0f));
}


void PointLight::addToShader(Shader &t_shader)
{
    t_shader.use();
 t_shader.addPointLight(m_constant, m_linear, m_quadratic, m_representation->getTranslation(), ambient(), diffuse(), specular());
}

PointLight::PointLight(glm::vec3 t_pos):
PointLight()
{
    m_representation->setScale(glm::vec3(0.1f));
    m_representation->setTranslation(t_pos);
}

SpotLight::SpotLight():
        PointLight(),
        m_direction(glm::vec3(0.0f, 0.f, -1.0f)),
        m_inner_cut_off(glm::cos(glm::radians(12.f))),
        m_outer_cut_off(glm::cos(glm::radians(16.f))),
        m_intensity(1.0f)
{

}

SpotLight::~SpotLight()
{

}

void SpotLight::addToShader(Shader &t_shader)
{
    t_shader.addSpotLight(m_direction, m_inner_cut_off, m_outer_cut_off, m_constant, m_linear, m_quadratic, m_intensity ,
                          m_representation->getTranslation(), ambient(), diffuse(), specular());
}

SpotLight::SpotLight(glm::vec3 t_pos):
        SpotLight()
{
    m_representation->setScale(glm::vec3(0.1f));
    m_representation->setTranslation(t_pos);
}
