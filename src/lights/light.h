//
// Created by Robin on 26/02/2020.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "core/shader.h"
#include "core/asset.h"
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


    /**
     * Add light to Shader
     * @param tr_shader
     */
    virtual void addToShader(Shader &tr_shader, int t_nbLights, int texIndex);


    virtual void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Asset>> &tr_models);
    [[nodiscard]] const std::string &getName()const{return m_name;}
    void setName(const std::string &tr_name){m_name=tr_name;}

    void drawLight(Shader &tr_mainShader,Shader &tr_optShader, GLuint t_glMode );




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
    void setPosition(const glm::vec3 &tr_pos){m_position=tr_pos;m_model->setTranslation(tr_pos);}
    void setSelected(bool t_isSelected){m_selected=t_isSelected;}
    void setToBeDestroyed(bool t_to_be_destroyed){m_to_be_destroyed=t_to_be_destroyed;}
    bool toBeDestroyed(){return m_to_be_destroyed;}

protected:
    void renderShadowMapToFbo(const glm::mat4 & tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                              const std::vector<std::shared_ptr<Asset>> &tr_models, int t_index);


    [[nodiscard]] const std::shared_ptr<Texture> &getShadowMap() const;

    [[nodiscard]] const glm::mat4 &getLightSpaceMatrix(int t_index) const;


    void addFrameBuffer(int t_width, int t_height, int t_numSamples){
        m_fbo=std::make_unique<FrameBuffer>(t_width,t_height,t_numSamples);
    }
    void addCubeMap(int t_index){m_fbo->addDepthCubeMap();}

    void drawBuffers(){
        m_fbo->addDepthTexture();
        m_fbo->drawBuffers();
        m_shadow_map=std::make_shared<Texture>(m_fbo->textures()[0],Texture::TextureType::SHADOW);

    }

    void addLightSpaceMatrix(const glm::mat4 &matrix){m_light_space_matrixes.emplace_back(matrix);}


private:
    std::unique_ptr<Asset> m_model;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_position;
    std::unique_ptr<FrameBuffer> m_fbo;
    std::shared_ptr<Texture> m_shadow_map;
    std::string m_name;
    std::vector<glm::mat4> m_light_space_matrixes;
    bool m_selected{false};
    bool m_to_be_destroyed{false};

};

#endif //ENGINE_LIGHT_H
