//
// Created by robin on 13/11/2020.
//

#include "dirLight.h"
#include <src/models/cube.h>


DirLight::DirLight():
        Light(glm::vec3(0.3f),glm::vec3(0.3f),glm::vec3(0.3f),glm::vec3(0.f)),
        m_direction(glm::vec3(0))
{

}

void DirLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex) {
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].position",position());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].direction", m_direction-position());
    t_shader.setMat4("dir_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("dir_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    Light::getShadowMap()->bindToGL(t_shader,31 - texIndex);
}



void DirLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                               const std::vector<std::shared_ptr<Model>> &tr_models) {
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 1.0f, far_plane = 15.f;
    lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    lightView = glm::lookAt(position(), m_direction, glm::vec3(0.0, 1.0, 0.0));
    Light::renderShadowMapToFbo(lightProjection * lightView, tr_shader,t_width,t_height,tr_models);
}