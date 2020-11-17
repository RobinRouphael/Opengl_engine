//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_DIRLIGHT_H
#define ENGINE_DIRLIGHT_H
#include "light.h"

class DirLight : public Light{
public:
    /**
     * Constructor
     */
    DirLight();

    /**
     * Destructor
     */
    ~DirLight() override=default;
    /**
     * Add Light to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;

    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Asset>> &tr_models) override;

    [[nodiscard]] const glm::vec3 &getDirection() const;

    void setDirection(const glm::vec3 &tr_direction);

private:
    glm::vec3 m_direction;

};


#endif //ENGINE_DIRLIGHT_H
