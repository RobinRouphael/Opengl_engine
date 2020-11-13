//
// Created by robin on 13/11/2020.
//

#include "spotLight.h"
#include <src/models/cube.h>
SpotLight::SpotLight():
        Light(glm::vec3(0.5f),glm::vec3(0.5f),glm::vec3(0.5f),glm::vec3(0.f)),
        m_constant{1.f},
        m_linear{0.14f},
        m_quadratic{0.07f},
        m_inner_cut_off(glm::cos(glm::radians(12.f))),
        m_outer_cut_off(glm::cos(glm::radians(16.f))),
        m_direction(glm::vec3(0.f))
{
}

void SpotLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex)
{
    t_shader.setVec3("spot_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("spot_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("spot_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("spot_light[" + std::to_string(t_nbLights) + "].position", position());
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].constant", m_constant);
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].linear", m_linear);
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].quadratic", m_quadratic);
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].quadratic", m_quadratic);
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].cutOff", m_inner_cut_off);
    t_shader.setFloat("spot_light[" + std::to_string(t_nbLights) + "].outerCutOff", m_outer_cut_off);
    t_shader.setVec3("spot_light[" + std::to_string(t_nbLights) + "].direction", m_direction-position());
    t_shader.setMat4("spot_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("spot_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    Light::getShadowMap()->bindToGL(t_shader,31 - texIndex);
}



void SpotLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                const std::vector<std::shared_ptr<Model>> &tr_models) {
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 50.f;
    lightProjection = glm::perspective<float>(m_outer_cut_off, 1.f,near_plane, far_plane);
    lightView = glm::lookAt(position(), m_direction, glm::vec3(0.0, 1.0, 0.0));
    Light::renderShadowMapToFbo(lightProjection * lightView, tr_shader,t_width,t_height,tr_models);
}