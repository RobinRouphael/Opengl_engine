//
// Created by robin on 01/11/2020.
//

#include "lightsManager.h"

void LightsManager::addPointLight() {

    m_light_constructor.emplace_back([this]()->void{
        auto pl=std::make_shared<PointLight>();
        pl->setName("point_light_"+std::to_string(m_point_lights.size()));
        m_point_lights.emplace_back(pl);
    });
    m_waiting_lights=true;
}

void LightsManager::addDirLight() {
    m_light_constructor.emplace_back([this]()->void {
        auto dl = std::make_shared<DirLight>();
        dl->setName("dir_light_" + std::to_string(m_dir_lights.size()));
        m_dir_lights.emplace_back(dl);
    });
    m_waiting_lights=true;
}

void LightsManager::addSpotLight() {
    m_light_constructor.emplace_back([this]()->void {
        auto sl = std::make_shared<SpotLight>();
        sl->setName("spot_light_" + std::to_string(m_spot_lights.size()));
        m_spot_lights.emplace_back(sl);
    });
    m_waiting_lights=true;
}

void LightsManager::addDirLight(const std::shared_ptr<DirLight> &tr_dir) {
    m_light_constructor.emplace_back([this,tr_dir]()->void {
        m_dir_lights.emplace_back(tr_dir);
    });
    m_waiting_lights=true;
}

void LightsManager::addSpotLight(const std::shared_ptr<SpotLight> &tr_spot) {
    m_light_constructor.emplace_back([this,tr_spot]()->void {
        m_spot_lights.emplace_back(tr_spot);
    });
    m_waiting_lights=true;
}

void LightsManager::addPointLight(const std::shared_ptr<PointLight> &tr_point) {
    m_light_constructor.emplace_back([this,tr_point]()->void {
        m_point_lights.emplace_back(tr_point);
    });
    m_waiting_lights=true;
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
                                     const std::vector<std::shared_ptr<Asset>> &tr_models) {
    for(auto &sl : m_spot_lights)
        sl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);
    for(auto &dl : m_dir_lights)
        dl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);
    for(auto &pl : m_point_lights)
        pl->renderShadowMap(tr_shader,t_width,t_height,tr_camTarget, tr_models);

}

void LightsManager::renderLights(Shader &tr_shader,Shader &tr_optShader, GLuint t_glMode) {
    for(auto &sl : m_spot_lights)
        sl->drawLight(tr_shader,tr_optShader,t_glMode);
    for(auto &dl : m_dir_lights)
        dl->drawLight(tr_shader,tr_optShader,t_glMode);
    for(auto &pl : m_point_lights)
        pl->drawLight(tr_shader,tr_optShader,t_glMode);

}



std::vector<std::string> LightsManager::getSpotList() const {
    std::vector<std::string> names;
    for(auto &l: m_spot_lights){
        names.emplace_back(l->getName());
    }
    return names;
}

std::vector<std::string> LightsManager::getDirList() const {
    std::vector<std::string> names;
    for(auto &l: m_dir_lights){
        names.emplace_back(l->getName());
    }
    return names;
}

std::vector<std::string> LightsManager::getPointList() const {
    std::vector<std::string> names;
    for(auto &l: m_point_lights){
        names.emplace_back(l->getName());
    }
    return names;
}

std::shared_ptr<SpotLight> LightsManager::selectSpotFromName(const std::string &tr_name) {
    for(auto &l: m_spot_lights){
        if(l->getName()==tr_name) {
            return l;
        }
    }
    return nullptr;
}

std::shared_ptr<DirLight> LightsManager::selectDirFromName(const std::string &tr_name) {
    for(auto &l: m_dir_lights){
        if(l->getName()==tr_name) {
            return l;
        }
    }
    return nullptr;
}

std::shared_ptr<PointLight> LightsManager::selectPointFromName(const std::string &tr_name) {
    for(auto &l: m_point_lights){
        if(l->getName()==tr_name) {

            return l;
        }
    }
    return nullptr;
}

void LightsManager::createWaitingLights() {
    if(m_waiting_lights){
        for(auto &lightConstr :m_light_constructor)
            lightConstr();
        m_light_constructor.clear();
    }
    m_waiting_lights=false;
}

void LightsManager::destroyWaitingLights() {
    for(auto it = m_spot_lights.begin(); it < m_spot_lights.end(); it++)
        if(it->get()->toBeDestroyed())
            m_spot_lights.erase(it);
    for(auto it = m_dir_lights.begin(); it < m_dir_lights.end(); it++)
        if(it->get()->toBeDestroyed())
            m_dir_lights.erase(it);
    for(auto it = m_point_lights.begin(); it < m_point_lights.end(); it++)
        if(it->get()->toBeDestroyed())
            m_point_lights.erase(it);
}





