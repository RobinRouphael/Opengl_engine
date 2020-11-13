//
// Created by robin on 01/11/2020.
//

#include "lightsManager.h"

void LightsManager::addPointLight() {
    m_point_lights.emplace_back(std::make_shared<PointLight>());
}

void LightsManager::addDirLight() {
    m_dir_lights.emplace_back(std::make_shared<DirLight>());
}

void LightsManager::addSpotLight() {
    m_spot_lights.emplace_back(std::make_shared<SpotLight>(glm::vec3(6,2,0)));
}


void LightsManager::addLightsToShader(Shader &tr_shader) {
    int index{0};

    for(size_t i = 0 ; i <   m_spot_lights.size() ; i++)
        m_spot_lights[i]->addToShader(tr_shader, i, index++);
    tr_shader.setInt("nb_spotLight", m_spot_lights.size());

    for(size_t i = 0 ; i <   m_dir_lights.size() ; i++)
        m_dir_lights[i]->addToShader(tr_shader, i, index++);
    tr_shader.setInt("nb_dirLight", m_dir_lights.size());

    for(size_t i = 0 ; i <   m_point_lights.size() ; i++)
        m_point_lights[i]->addToShader(tr_shader, i, index++);
    tr_shader.setInt("nb_pointLight", m_point_lights.size());

}

void LightsManager::renderShadowMaps(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                     const std::vector<std::shared_ptr<Model>> &tr_models) {
    for(auto &sl : m_spot_lights)
        sl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);
    for(auto &dl : m_dir_lights)
        dl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);
    for(auto &pl : m_point_lights)
        pl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);

}

void LightsManager::renderLights(Shader &tr_shader, GLuint t_glMode) {
    for(auto &sl : m_spot_lights)
        sl->drawLight(tr_shader);
    for(auto &dl : m_dir_lights)
        dl->drawLight(tr_shader);
    for(auto &pl : m_point_lights)
        pl->drawLight(tr_shader);

}
