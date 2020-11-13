//
// Created by Robin on 26/02/2020.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "core/shader.h"
#include "core/model.h"
#include "core/frameBuffer.h"

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
     * @param t_position
     */
    Light(const glm::vec3 &t_ambient, const glm::vec3 &t_diffuse, const glm::vec3 &t_specular, const glm::vec3 &tr_position);
    /**
     * Destructor
     */
    virtual ~Light()=default;

    Light(const Light &) = delete;

    Light(Light &&) = delete;

    Light &operator=(const Light &) = delete;

    Light &&operator=(Light &&) = delete;


    /**
     * Add light to Shader
     * @param tr_shader
     */
    virtual void addToShader(Shader &tr_shader, int t_nbLights, int texIndex)=0;


    virtual void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Model>> &tr_models)=0;

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
    /**
     * Position getter
     * @return
     */
    [[nodiscard]] const glm::vec3 & position() const { return m_position; }

    void renderShadowMapToFbo(const glm::mat4 & tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                              const std::vector<std::shared_ptr<Model>> &tr_models);
    [[nodiscard]] const std::shared_ptr<Texture> &getShadowMap() const;

    [[nodiscard]] const glm::mat4 &getLightSpaceMatrix() const;


private:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_position;
    std::unique_ptr<FrameBuffer> m_fbo;

    glm::mat4 m_light_space_matrix;

};

#endif //ENGINE_LIGHT_H
