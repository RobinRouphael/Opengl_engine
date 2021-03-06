//
// Created by robin on 13/11/2020.
//

#ifndef ENGINE_POINTLIGHT_H
#define ENGINE_POINTLIGHT_H
#include "light.h"

class PointLight : public Light {

public:
    /**
     * Constructor
     * Initialize Pointlight from default values
     */
    PointLight();
    /**
     * Destructor
     */
    ~PointLight() override =default;
    /**
     * Add pointLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
    /**
     * Constant getter
     * @return
     */
    [[nodiscard]] GLfloat getConst()const {return m_constant;}
    /**
     * Linear getter
     * @return
     */
    [[nodiscard]] GLfloat getLin() const{return m_linear;}
    /**
     * Quadratic getter
     * @return
     */
    [[nodiscard]] GLfloat getQuad() const{return m_quadratic;}
    /**
     * Quadratic setter
     * @param t_quad
     */
    void setQuadratic(double t_quad){ m_quadratic = t_quad;}
    /**
     * Linear setter
     * @param t_linear
     */
    void setLinear(double t_linear){ m_linear = t_linear;}
    /**
     * Constant setter
     * @param t_const
     */
    void setConstant(double t_const){ m_constant = t_const;}
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


private:
    GLfloat m_constant; //Constant term
    GLfloat m_linear;   //Linear term
    GLfloat m_quadratic;    //Quadratic term
};


#endif //ENGINE_POINTLIGHT_H
