//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_SPOTLIGHT_H
#define ENGINE_SPOTLIGHT_H
#include "light.h"

class SpotLight : public Light{
public:
    /**
     * Constructor
     */
    SpotLight();
    /**
     * Constructor
     * @param t_pos
     */
    explicit SpotLight(glm::vec3 t_pos);
    /**
     * Destructor
     */
    ~SpotLight() override=default;
    /**
     * Add spotLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Model>> &tr_models) override;
private:
    float m_inner_cut_off;
    float m_outer_cut_off;
    glm::vec3 m_direction;
    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_quadratic;

};


#endif //ENGINE_SPOTLIGHT_H
