//
// Created by robin on 01/11/2020.
//

#ifndef ENGINE_LIGHTSMANAGER_H
#define ENGINE_LIGHTSMANAGER_H


#include <vector>
#include <functional>
#include "shader.h"
#include "lights/light.h"
#include "lights/spotLight.h"
#include "lights/dirLight.h"
#include "lights/pointLight.h"
class LightsManager {
public:
    LightsManager() = default;
    ~LightsManager() = default;
    void addLightsToShader(Shader &tr_shader);
    void renderShadowMaps(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                          const std::vector<std::shared_ptr<Asset>> &tr_models);
    void renderLights(Shader &tr_shader,Shader &tr_optShader,GLuint t_glMode );


    [[nodiscard]] std::vector<std::string> getSpotList() const;
    [[nodiscard]] std::vector<std::string> getDirList() const;
    [[nodiscard]] std::vector<std::string> getPointList() const;



    void addPointLight();
    void addDirLight();
    void addSpotLight();
    void addPointLight(const std::shared_ptr<PointLight>&  tr_point);
    void addDirLight(const std::shared_ptr<DirLight>&  tr_dir);
    void addSpotLight(const std::shared_ptr<SpotLight>&  tr_spot);
    void createWaitingLights();
    void destroyWaitingLights();
    std::shared_ptr<SpotLight>selectSpotFromName(const std::string& tr_name);
    std::shared_ptr<DirLight>selectDirFromName(const std::string& tr_name);
    std::shared_ptr<PointLight>selectPointFromName(const std::string& tr_name);
private:
    std::vector<std::shared_ptr<SpotLight>> m_spot_lights;
    std::vector<std::shared_ptr<DirLight>> m_dir_lights;
    std::vector<std::shared_ptr<PointLight>> m_point_lights;
    std::vector<std::function<void()>> m_light_constructor;
    bool m_waiting_lights{false};
};


#endif //ENGINE_LIGHTSMANAGER_H
