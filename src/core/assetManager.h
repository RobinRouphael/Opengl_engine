//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_ASSETMANAGER_H
#define ENGINE_ASSETMANAGER_H


#include <src/models/sphere.h>
#include <src/models/icosphere.h>
#include <src/models/metaball.h>
#include "asset.h"

class AssetManager {
public:
    AssetManager()=default;
    ~AssetManager()=default;
    const std::shared_ptr<Sphere> &selectSphereFromName(const std::string &tr_name);
    const std::shared_ptr<Icosphere> &selectIcoSphereFromName(const std::string &tr_name);
    const std::shared_ptr<Asset> &selectCustomFromName(const std::string &tr_name);
    const std::shared_ptr<MetaBall> &selectMetaballFromName(const std::string &tr_name);
    [[nodiscard]] std::vector<std::string> getSphereList() const;
    [[nodiscard]] std::vector<std::string> getIcoSphereList() const;
    [[nodiscard]] std::vector<std::string> getCustomList() const;
    [[nodiscard]] std::vector<std::string> getMetaBallList() const;
    const std::vector<std::shared_ptr<Asset>> &getAssets();
    void createWaitingAssets();
    void addSphere();
    void addIcoSphere();
    void addMetaBall();
    void addAssimpFromFile(const std::string &location);
    void addAsset(const std::shared_ptr<Asset>&tr_asset);
    void renderOpaqueAssets(Shader &tr_shader,Shader &tr_optShader,GLuint t_glMode );
    void renderTransparentAssets(Shader &tr_shader,Shader &tr_optShader,GLuint t_glMode );
    void destroyWaitingAssets();
private:
    bool m_waiting_assets{false};
    std::vector<std::function<void()>> m_asset_constructor;
    std::vector<std::shared_ptr<Sphere>> m_spheres;
    std::vector<std::shared_ptr<Icosphere>> m_ico_spheres;
    std::vector<std::shared_ptr<MetaBall>> m_meta_ball;
    std::vector<std::shared_ptr<Asset>> m_custom;

    std::vector<std::shared_ptr<Asset>> m_assets;

};


#endif //ENGINE_ASSETMANAGER_H
