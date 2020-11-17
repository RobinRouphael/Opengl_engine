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
     * Destructor
     */
    ~SpotLight() override=default;
    /**
     * Add spotLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Asset>> &tr_models) override;

    [[nodiscard]] const glm::vec3 &getDirection() const{return m_target;}

    void setDirection(const glm::vec3 &tr_direction){ m_target =tr_direction;}

    void setInnerCO(float t_ico){m_inner_cut_off=t_ico;}
    [[nodiscard]] float getInnerCO() const{return m_inner_cut_off;}

    void setOuterCO(float t_oco){m_outer_cut_off=t_oco;}
    [[nodiscard]] float getOuterCO() const{return m_outer_cut_off;}

    void setConstant(float t_const){m_constant=t_const;}
    [[nodiscard]] float getConstant() const{return m_constant;}

    void setLinear(float t_lin){m_linear=t_lin;}
    [[nodiscard]] float getLinear() const{return m_linear;}

    void setQuad(float t_quad){m_quadratic=t_quad;}
    [[nodiscard]] float getQuad() const{return m_quadratic;}


private:
    float m_inner_cut_off;
    float m_outer_cut_off;
    glm::vec3 m_target;
    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_quadratic;

};


#endif //ENGINE_SPOTLIGHT_H
