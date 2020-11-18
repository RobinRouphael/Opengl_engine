//
// Created by robin on 13/11/2020.
//

#include <src/models/assimpmodel.h>
#include "assetManager.h"

const std::shared_ptr<Sphere> &AssetManager::selectSphereFromName(const std::string &tr_name) {
    for(auto &a: m_spheres){
        if(a->getName()==tr_name) {
            return a;
        }
    }
    return nullptr;
}

const std::shared_ptr<Icosphere> &AssetManager::selectIcoSphereFromName(const std::string &tr_name) {
    for(auto &a: m_ico_spheres){
        if(a->getName()==tr_name) {
            return a;
        }
    }
    return nullptr;
}

const std::shared_ptr<Asset> &AssetManager::selectCustomFromName(const std::string &tr_name) {
    for(auto &a: m_custom){
        if(a->getName()==tr_name) {
            return a;
        }
    }
    return nullptr;
}

const std::shared_ptr<MetaBall> &AssetManager::selectMetaballFromName(const std::string &tr_name) {
    for(auto &a: m_meta_ball){
        if(a->getName()==tr_name) {
            return a;
        }
    }
    return nullptr;
}

std::vector<std::string> AssetManager::getMetaBallList() const {
    std::vector<std::string> names;
    for(auto &l: m_meta_ball){
        names.emplace_back(l->getName());
    }
    return names;
}

std::vector<std::string> AssetManager::getSphereList() const {
    std::vector<std::string> names;
    for(auto &l: m_spheres){
        names.emplace_back(l->getName());
    }
    return names;
}

std::vector<std::string> AssetManager::getIcoSphereList() const {
    std::vector<std::string> names;
    for(auto &l: m_ico_spheres){
        names.emplace_back(l->getName());
    }
    return names;
}

std::vector<std::string> AssetManager::getCustomList() const {
    std::vector<std::string> names;
    for(auto &l: m_custom){
        names.emplace_back(l->getName());
    }
    return names;
}

void AssetManager::addSphere() {
    m_asset_constructor.emplace_back([this]()->void{
        auto sphere = std::make_shared<Sphere>();
        sphere->setName("sphere_"+std::to_string(m_spheres.size()));
        m_spheres.emplace_back(sphere);
        m_assets.emplace_back(sphere);
    });
    m_waiting_assets=true;

}

void AssetManager::addIcoSphere() {
    m_asset_constructor.emplace_back([this]()->void {
        auto icosphere = std::make_shared<Icosphere>();
        icosphere->setName("ico_sphere_" + std::to_string(m_ico_spheres.size()));
        m_ico_spheres.emplace_back(icosphere);
        m_assets.emplace_back(icosphere);
    });
    m_waiting_assets=true;
}
void AssetManager::addMetaBall() {
    m_asset_constructor.emplace_back([this]()->void {
        auto metaball = std::make_shared<MetaBall>();
        metaball->setName("meta_ball_" + std::to_string(m_meta_ball.size()));
        m_meta_ball.emplace_back(metaball);
        m_assets.emplace_back(metaball);
    });
    m_waiting_assets=true;
}
void AssetManager::addAsset(const std::shared_ptr<Asset>& tr_asset) {
    m_asset_constructor.emplace_back([this,tr_asset]()->void {
        m_assets.emplace_back(tr_asset);
        m_custom.emplace_back(tr_asset);
    });
    m_waiting_assets=true;
}
void AssetManager::addAssimpFromFile(const std::string &location) {
    m_asset_constructor.emplace_back([this,location]()->void {
        auto assimp = std::make_shared<AssimpModel>(location);
        assimp->setName("custom_" + std::to_string(m_custom.size()));
        m_custom.emplace_back(assimp);
        m_assets.emplace_back(assimp);
    });
    m_waiting_assets=true;
}

void AssetManager::renderOpaqueAssets(Shader &tr_shader, Shader &tr_optShader, GLuint t_glMode) {
    for (auto &a: m_assets){
        a->drawModel(tr_shader, t_glMode);
        tr_optShader.use();
        a->drawSelectionEdges(tr_optShader,t_glMode);
        tr_shader.use();
    }
}

void AssetManager::renderTransparentAssets(Shader &tr_shader, Shader &tr_optShader, GLuint t_glMode) {
    for (auto &a: m_assets){
        if(a->getShaderType()==Asset::ShaderType::TRANSPARENT)
            a->drawModel(tr_shader, t_glMode);
    }
}

const std::vector<std::shared_ptr<Asset>> &AssetManager::getAssets() {
    return m_assets;
}

void AssetManager::createWaitingAssets() {
    if(m_waiting_assets){
        for(auto &assetConstr :m_asset_constructor)
            assetConstr();
        m_asset_constructor.clear();
    }
    m_waiting_assets=false;
}

void AssetManager::destroyWaitingAssets() {
    for(auto it = m_assets.begin(); it < m_assets.end(); it++)
        if(it->get()->toBeDestroyed())
            m_assets.erase(it);
    for(auto it = m_custom.begin(); it < m_custom.end(); it++)
        if(it->get()->toBeDestroyed())
            m_custom.erase(it);
    for(auto it = m_ico_spheres.begin(); it < m_ico_spheres.end(); it++)
        if(it->get()->toBeDestroyed())
            m_ico_spheres.erase(it);
    for(auto it = m_spheres.begin(); it < m_spheres.end(); it++)
        if(it->get()->toBeDestroyed())
            m_spheres.erase(it);
    for(auto it = m_meta_ball.begin(); it < m_meta_ball.end(); it++)
        if(it->get()->toBeDestroyed())
            m_meta_ball.erase(it);
}








