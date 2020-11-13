//
// Created by robin on 01/11/2020.
//

#ifndef ENGINE_LIGHTSMANAGER_H
#define ENGINE_LIGHTSMANAGER_H


#include <vector>
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
                          const std::vector<std::shared_ptr<Model>> &tr_models);
    void renderLights(Shader &tr_shader,GLuint t_glMode );

    std::shared_ptr<Texture> tex(){return m_point_lights[1]->m_shadow_map;}


    void addPointLight();
    void addDirLight();
    void addSpotLight();
private:
    std::vector<std::shared_ptr<SpotLight>> m_spot_lights;
    std::vector<std::shared_ptr<DirLight>> m_dir_lights;
    std::vector<std::shared_ptr<PointLight>> m_point_lights;
};


#endif //ENGINE_LIGHTSMANAGER_H
