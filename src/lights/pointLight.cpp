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

    addFrameBuffer(2048, 2048, 1);
    drawBuffers();
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
    t_shader.setInt("point_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    Light::getShadowMap()->bindToGL(t_shader, 31 - texIndex);
    t_shader.setMat4("point_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix",
                         getLightSpaceMatrix());

}

void PointLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Asset>> &tr_models) {

    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = 2.0f, far_plane = 50.f;
    glm::vec3 dir = glm::normalize(tr_camTarget - position());
    glm::vec3 worldUp = glm::vec3{0.f, 1.f, 0.f};
    if (dir == worldUp || dir == -worldUp) worldUp = glm::vec3{1.f, 0.f, 0.f};
    glm::vec3 right = glm::cross(dir, worldUp);
    glm::vec3 up = glm::cross(right, glm::normalize(dir));
    lightProjection = glm::perspective(glm::radians(90.0f), 1.f, near_plane, far_plane);
    lightView = glm::lookAt(position(),glm::normalize(dir), up);
    Light::renderShadowMapToFbo(lightProjection * lightView, tr_shader,t_width,t_height,tr_models,0);

}