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
    /**
     * Compute light space matrix before calling protected base class function to perform shared fbo's operations
     * @param tr_shader
     * @param t_width
     * @param t_height
     * @param tr_camTarget
     * @param tr_models
     */
    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Asset>> &tr_models) override;
    /**
     * Target getter
     * @return
     */
    [[nodiscard]] const glm::vec3 &getTarget() const{return m_target;}
    /**
     * Target setter
     * @param tr_target
     */
    void setTarget(const glm::vec3 &tr_target){ m_target =tr_target;}
    /**
     * Inner cut-off setter
     * @param t_ico
     */
    void setInnerCO(float t_ico){m_inner_cut_off=t_ico;}
    /**
     * Inner cut-off getter
     * @return
     */
    [[nodiscard]] float getInnerCO() const{return m_inner_cut_off;}
    /**
     * Outer cut-off setter
     * @param t_oco
     */
    void setOuterCO(float t_oco){m_outer_cut_off=t_oco;}
    /**
     * Outer cut-off getter
     * @return
     */
    [[nodiscard]] float getOuterCO() const{return m_outer_cut_off;}
    /**
     * Constant term setter
     * @param t_const
     */
    void setConstant(float t_const){m_constant=t_const;}
    /**
     * Constant term getter
     * @return
     */
    [[nodiscard]] float getConstant() const{return m_constant;}
    /**
     * Linear term setter
     * @param t_lin
     */
    void setLinear(float t_lin){m_linear=t_lin;}
    /**
     * Linear term getter
     * @return
     */
    [[nodiscard]] float getLinear() const{return m_linear;}
    /**
     * Quadratic term setter
     * @param t_quad
     */
    void setQuad(float t_quad){m_quadratic=t_quad;}
    /**
     * Quadratic term getter
     * @return
     */
    [[nodiscard]] float getQuad() const{return m_quadratic;}


private:
    float m_inner_cut_off;  //Inner cut-off angle in radians
    float m_outer_cut_off;  //Outer cut-off angle in radians
    glm::vec3 m_target; //Target position
    GLfloat m_constant; //Constant term
    GLfloat m_linear;   //Linear term
    GLfloat m_quadratic;    //Quadratic term

};


#endif //ENGINE_SPOTLIGHT_H
