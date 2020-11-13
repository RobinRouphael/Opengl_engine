//
// Created by robin on 13/11/2020.
//

#include "pointLight.h"
#include <src/models/cube.h>


PointLight::PointLight():
        Light(glm::vec3(1.f),glm::vec3(1.f),glm::vec3(1.f),glm::vec3(0.f)),
        m_constant{1.f},
        m_linear{0.14f},
        m_quadratic{0.07f}

{
}


void PointLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex)
{
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].position", position());
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].constant", m_constant);
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].linear", m_linear);
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].quadratic", m_quadratic);
    t_shader.setMat4("point_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("point_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    Light::getShadowMap()->bindToGL(t_shader,31 - texIndex);
}



void PointLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Model>> &tr_models) {


    glm::vec3 center = tr_camTarget;
    glm::vec3 lightToCenter = center - position();
    glm::vec3 right = glm::cross(glm::normalize(lightToCenter), glm::vec3{0.f, 1.f, 0.f});
    glm::vec3 up = glm::cross(right, glm::normalize(lightToCenter));
    glm::mat4 lightView = glm::lookAt(position(), position() + glm::normalize(lightToCenter), up);
    glm::mat4 lightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 1.f, 2.f * glm::length(lightToCenter));
    Light::renderShadowMapToFbo(lightProj * lightView, tr_shader,t_width,t_height,tr_models);

}