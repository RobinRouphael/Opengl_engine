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
     * Add light to shader
     * @param tr_shader
     * @param t_nbLights
     * @param texIndex
     */
    virtual void addToShader(Shader &tr_shader, int t_nbLights, int texIndex);

    /**
     * Render ShadowMap of the light
     * Reimplemented by the descendent, compute the light space matrix before calling the private func renderShadowMapToFbo()
     * @param tr_shader
     * @param t_width
     * @param t_height
     * @param tr_camTarget
     * @param tr_models
     */
    virtual void renderShadowMap(Shader &tr_shader, int t_width, int t_height, const glm::vec3 &tr_camTarget,
                                 const std::vector<std::shared_ptr<Asset>> &tr_models);
    /**
     * Name getter
     * @return
     */
    [[nodiscard]] const std::string &getName()const{return m_name;}
    /**
     * Name setter
     * @param tr_name
     */
    void setName(const std::string &tr_name){m_name=tr_name;}
    /**
     * Draw the light's representation
     * @param tr_mainShader
     * @param tr_optShader
     * @param t_glMode
     */
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
    /**
     * Position setter
     * @param tr_pos
     */
    void setPosition(const glm::vec3 &tr_pos){m_position=tr_pos;m_model->setTranslation(tr_pos);}
    /**
     * Set the light to selected or not
     * @param t_isSelected
     */
    void setSelected(bool t_isSelected){m_selected=t_isSelected;}
    /**
     * Set the light to be destroyed in the next frame (Thread management)
     * @param t_to_be_destroyed
     */
    void setToBeDestroyed(bool t_to_be_destroyed){m_to_be_destroyed=t_to_be_destroyed;}
    /**
     * True if the light has to be destroyed this frame (Thread management)
     * @return
     */
    bool toBeDestroyed(){return m_to_be_destroyed;}

protected:
    /**
     * Refactoring
     * Common to all type of lights, perform the actual rendering of the shadowMap
     * @param tr_lightSpaceMatrix
     * @param tr_shader
     * @param t_width
     * @param t_height
     * @param tr_models
     * @param t_index
     */
    void renderShadowMapToFbo(const glm::mat4 & tr_lightSpaceMatrix, Shader &tr_shader, int t_width, int t_height,
                              const std::vector<std::shared_ptr<Asset>> &tr_models, int t_index);

    /**
     * ShadowMap getter
     * @return
     */
    [[nodiscard]] const std::shared_ptr<Texture> &getShadowMap() const;
    /**
     * Light space matrix getter
     * @return
     */
    [[nodiscard]] const glm::mat4 &getLightSpaceMatrix() const;

    /**
     * Add a FrameBuffer
     * @param t_width
     * @param t_height
     * @param t_numSamples
     */
    void addFrameBuffer(int t_width, int t_height, int t_numSamples){
        m_fbo=std::make_unique<FrameBuffer>(t_width,t_height,t_numSamples);
    }
    /**
     * Add a cubeMap to the current FrameBuffer (for omnidirectionnal shadows)
     */
    void addCubeMap(){m_fbo->addDepthCubeMap();}
    /**
     * Add a Depth Texture, draw Buffers and create ShadowMap texture
     */
    void drawBuffers(){
        m_fbo->addDepthTexture();
        m_fbo->drawBuffers();
        m_shadow_map=std::make_shared<Texture>(m_fbo->textures()[0],Texture::TextureType::SHADOW);

    }


private:
    std::unique_ptr<Asset> m_model; //Light physical representation
    glm::vec3 m_ambient;    //Ambient color of the light
    glm::vec3 m_diffuse;    //Diffuse color of the light
    glm::vec3 m_specular;   //Specular color of the light
    glm::vec3 m_position;   //Position of the light
    std::unique_ptr<FrameBuffer> m_fbo; //Associated FrameBuffer
    std::shared_ptr<Texture> m_shadow_map;  //Associated ShadowMap texture
    std::string m_name; //Name
    glm::mat4 m_light_space_matrix; //Associated light space matrix
    bool m_selected{false}; //Is the light selected
    bool m_to_be_destroyed{false};  //Is the light has to be destroyed

};

#endif //ENGINE_LIGHT_H
