//
// Created by Robin on 26/02/2020.
//


#include "light.h"

Light::Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const glm::vec3 &tr_position):
        m_ambient{t_ambient},
        m_diffuse{t_diffuse},
        m_specular{t_specular},
        m_position(tr_position),
        m_fbo{std::make_unique<FrameBuffer>(2048,2048,1)}
{
    m_fbo->addDepthTexture();
    m_fbo->drawBuffers();
    m_shadow_map = std::make_shared<Texture>(m_fbo->textures()[0], Texture::TextureType::SHADOW);
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
































