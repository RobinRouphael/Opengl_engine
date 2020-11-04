//
// Created by Robin on 26/02/2020.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "shader.h"
#include "model.h"
#include "frameBuffer.h"

class Light {
    /**
     * Base class for lights
     */
public:
    /**
     * Constructor
     * @param t_ambient
     * @param t_diffuse
     * @param t_specular
     * @param t_representation
     */
    Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const std::shared_ptr<Model> &t_representation);
    /**
     * Destructor
     */
    virtual ~Light();

    Light(const Light &) = delete;

    Light(Light &&) = delete;

    Light &operator=(const Light &) = delete;

    Light &&operator=(Light &&) = delete;

    /**
     * Draw light model
     * @param tr_shader
     */
    void drawLight(Shader &tr_shader);
    /**
     * Add light to Shader
     * @param tr_shader
     */
    virtual void addToShader(Shader &tr_shader, int t_nbLights, int texIndex);


    virtual void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Model>> &tr_models);

    std::shared_ptr<Texture> m_shadow_map;
protected:
    /**
     * Ambient getter
     * @return
     */
    [[nodiscard]] const glm::vec3 & ambient() const { return m_ambient; }
    /**
     * Ambient setter
     * @return
     */
    glm::vec3 & ambient() { return m_ambient; }
    /**
     * Diffuse getter
     * @return
     */
    [[nodiscard]] const glm::vec3 & diffuse() const { return m_diffuse; }
    /**
     * Diffuse setter
     * @return
     */
    glm::vec3 & diffuse() { return m_diffuse; }
    /**
     * Specular getter
     * @return
     */
    [[nodiscard]] const glm::vec3 & specular() const { return m_specular; }
    /**
     * Specular setter
     * @return
     */
    glm::vec3 & specular() { return m_specular; }

    void renderShadowMapToFbo(const glm::mat4 & tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                              const std::vector<std::shared_ptr<Model>> &tr_models);
    [[nodiscard]] const std::shared_ptr<Texture> &getShadowMap() const;

    [[nodiscard]] const glm::mat4 &getLightSpaceMatrix() const;


private:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    std::unique_ptr<FrameBuffer> m_fbo;

    glm::mat4 m_light_space_matrix;

protected:

    std::shared_ptr<Model> m_representation; //Model of light
};


class PointLight : public Light {

public:
    /**
     * Constructor
     * Initialize light from default values
     */
    PointLight();
    /**
     * Constructor
     * Initialize light from default values
     * @param position
     */
    PointLight(glm::vec3 t_pos);
    /**
     * Destructor
     */
    ~PointLight();
    /**
     * Add pointLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
    /**
     * Constant getter
     * @return
     */
    GLfloat getConst()const {return m_constant;}
    /**
     * Linear getter
     * @return
     */
    GLfloat getLin() const{return m_linear;}
    /**
     * Quadratic getter
     * @return
     */
    GLfloat getQuad() const{return m_quadratic;}
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

    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Model>> &tr_models);


protected:
    GLfloat m_constant;
    GLfloat m_linear;
    GLfloat m_quadratic;
};


class SpotLight : public PointLight{
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
    ~SpotLight() override;
    /**
     * Add spotLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
private:
    glm::vec3 m_direction;
    float m_inner_cut_off;
    float m_outer_cut_off;
    float m_intensity;
};

class DirLight : public Light{
public:
    /**
     * Constructor
     */
    DirLight();

    /**
     * Destructor
     */
    ~DirLight() override;
    /**
     * Add spotLight to Shader
     * @param t_shader
     */
    void addToShader(Shader &t_shader, int t_nbLights, int texIndex) override;
    void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                         const std::vector<std::shared_ptr<Model>> &tr_models) override;
private:
    glm::vec3 m_direction;
};


#endif //ENGINE_LIGHT_H
