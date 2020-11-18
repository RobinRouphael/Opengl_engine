//
// Created by robin on 13/11/2020.
//

#include "dirLight.h"
#include <src/models/cube.h>


DirLight::DirLight():
        Light(glm::vec3(0.01f),glm::vec3(0.3f),glm::vec3(0.3f),glm::vec3(0.f)),
        m_direction(glm::vec3(0,-1,0))
{
    addFrameBuffer(4096,4096,1);
    drawBuffers();
}

void DirLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex) {
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].position",position());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].direction", glm::normalize(m_direction));
    t_shader.setMat4("dir_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("dir_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    Light::getShadowMap()->bindToGL(t_shader,31 - texIndex);
}

void DirLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                               const std::vector<std::shared_ptr<Asset>> &tr_models) {
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 2.0f, far_plane = 50.f;
    glm::vec3 worldUp = glm::vec3{0.f, 1.f, 0.f};
    if (m_direction == worldUp || m_direction == -worldUp) worldUp = glm::vec3{1.f, 0.f, 0.f};
    glm::vec3 right = glm::cross(glm::normalize(m_direction), worldUp);
    glm::vec3 up = glm::cross(right, glm::normalize(m_direction));
    lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, near_plane, far_plane);
    lightView = glm::lookAt(position(),position()+glm::normalize(m_direction), up);
    Light::renderShadowMapToFbo(lightProjection * lightView, tr_shader,t_width,t_height,tr_models,0);
}

const glm::vec3 &DirLight::getDirection() const {
    return m_direction;
}

void DirLight::setDirection(const glm::vec3 &tr_direction) {
    m_direction = tr_direction;
}
