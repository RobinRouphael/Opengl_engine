//
// Created by Robin on 26/02/2020.
//

#include <src/models/cube.h>
#include "light.h"

Light::Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const std::shared_ptr<Model> &t_representation):
        m_ambient{t_ambient},
        m_diffuse{t_diffuse},
        m_specular{t_specular},
        m_representation(t_representation),
        m_fbo{std::make_unique<FrameBuffer>(2048,2048,1)}
{
    m_fbo->addDepthTexture();
    m_fbo->drawBuffers();
    m_shadow_map = std::make_shared<Texture>(m_fbo->textures()[0], Texture::TextureType::SHADOW);
}

Light::~Light()
{

}

void Light::addToShader(Shader &tr_shader, int t_nbLights, int texIndex)
{

}

void Light::drawLight(Shader &tr_shader)
{
    m_representation->drawModel(tr_shader, GL_TRIANGLES);
}

void Light::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                            const std::vector<std::shared_ptr<Model>> &tr_models) {

}

void Light::renderShadowMapToFbo(const glm::mat4 &tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                                 const std::vector<std::shared_ptr<Model>> &tr_models) {
    m_fbo->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    m_light_space_matrix = tr_lightSpaceMatrix;
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    tr_shader.setMat4("lightSpaceMatrix", m_light_space_matrix);
    for(auto &m : tr_models)
        m->drawModel(tr_shader, GL_TRIANGLES);
    //glDisable(GL_CULL_FACE);
    m_fbo->stop(t_width, t_height);
}

const std::shared_ptr<Texture> &Light::getShadowMap() const {
    return m_shadow_map;
}

const glm::mat4 &Light::getLightSpaceMatrix() const {
    return m_light_space_matrix;
}




PointLight::~PointLight(){}

PointLight::PointLight():
        Light(glm::vec3(1.f),glm::vec3(1.f),glm::vec3(1.f),std::make_shared<Cube>()),
        m_constant{1.f},
        m_linear{0.14f},
        m_quadratic{0.07f}

{
    m_representation->setTranslation(glm::vec3(0.7f, 0.2f, 2.0f));
}


void PointLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex)
{
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("point_light[" + std::to_string(t_nbLights) + "].position", m_representation->getTranslation());
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].constant", m_constant);
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].linear", m_linear);
    t_shader.setFloat("point_light[" + std::to_string(t_nbLights) + "].quadratic", m_quadratic);
    t_shader.setMat4("point_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("point_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    getShadowMap()->bindToGL(t_shader,31 - texIndex);
}

PointLight::PointLight(glm::vec3 t_pos):
PointLight()
{
    m_representation->setScale(glm::vec3(0.1f));
    m_representation->setTranslation(t_pos);
}

void PointLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Model>> &tr_models) {


    glm::vec3 center = tr_camTarget;
    glm::vec3 lightToCenter = center - m_representation->getTranslation();
    glm::vec3 right = glm::cross(glm::normalize(lightToCenter), glm::vec3{0.f, 1.f, 0.f});
    glm::vec3 up = glm::cross(right, glm::normalize(lightToCenter));
    glm::mat4 lightView = glm::lookAt(m_representation->getTranslation(), m_representation->getTranslation() + glm::normalize(lightToCenter), up);
    glm::mat4 lightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 1.f, 2.f * glm::length(lightToCenter));
    renderShadowMapToFbo(lightProj * lightView, tr_shader,t_width,t_height,tr_models);

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

void SpotLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex)
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

DirLight::~DirLight() {

}

void DirLight::addToShader(Shader &t_shader, int t_nbLights, int texIndex) {
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].ambient", ambient());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].diffuse", diffuse());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].specular", specular());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].position", m_representation->getTranslation());
    t_shader.setVec3("dir_light[" + std::to_string(t_nbLights) + "].direction", m_direction);
    t_shader.setMat4("dir_light[" + std::to_string(t_nbLights) + "].shadow.lightSpaceMatrix", getLightSpaceMatrix());
    t_shader.setInt("dir_light[" + std::to_string(t_nbLights) + "].shadow.shadowMap", 31 - texIndex);
    getShadowMap()->bindToGL(t_shader,31 - texIndex);
}

DirLight::DirLight():
        Light(glm::vec3(0.5f),glm::vec3(2.f),glm::vec3(1.f),std::make_shared<Cube>())
{
    m_representation->setScale(glm::vec3(0.1f));
    m_representation->setTranslation(glm::vec3(4.5, 2, 4.5));
}

void DirLight::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                               const std::vector<std::shared_ptr<Model>> &tr_models) {
    Light::renderShadowMap(tr_shader, t_width, t_height, tr_camTarget, tr_models);
}
