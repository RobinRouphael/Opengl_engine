//
// Created by Robin on 26/02/2020.
//


#include <src/models/cube.h>
#include "light.h"

Light::Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const glm::vec3 &tr_position):
        m_ambient{t_ambient},
        m_diffuse{t_diffuse},
        m_specular{t_specular},
        m_position(tr_position),
        m_selected{false},
        m_model{std::make_unique<Cube>()}
{
    m_model->setScale(glm::vec3(0.1f));

}

void Light::renderShadowMapToFbo(const glm::mat4 &tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                                 const std::vector<std::shared_ptr<Asset>> &tr_models,int t_index) {
    m_fbo->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    m_light_space_matrix=tr_lightSpaceMatrix;
    glEnable(GL_DEPTH_TEST);

    tr_shader.setMat4("lightSpaceMatrix", m_light_space_matrix);
    for(auto &m : tr_models)
        m->drawModel(tr_shader, GL_TRIANGLES);

    m_fbo->stop(t_width, t_height);
}

const std::shared_ptr<Texture> &Light::getShadowMap() const {
    return m_shadow_map;
}

const glm::mat4 &Light::getLightSpaceMatrix() const {
    return m_light_space_matrix;
}

void Light::renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                            const std::vector<std::shared_ptr<Asset>> &tr_models) {

}

void Light::addToShader(Shader &tr_shader, int t_nbLights, int texIndex) {

}

void Light::drawLight(Shader &tr_mainShader, Shader &tr_optShader, GLuint t_glMode) {
    m_model->drawModel(tr_mainShader,t_glMode);
    if(m_selected){
        tr_optShader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(1);
        glEnable( GL_POLYGON_OFFSET_LINE );
        glPolygonOffset( -1, -1 );
        m_model->drawModel(tr_optShader,t_glMode);
        glDisable( GL_POLYGON_OFFSET_LINE );
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        tr_mainShader.use();
    }
}


































