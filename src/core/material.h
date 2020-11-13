//
// Created by Robin on 10/03/2020.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H



#include <opengl_stuff.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/textures/texture.h>
#include <vector>
#include <memory>

class Material {
public:
    Material();
    ~Material() = default;

    Material(const Material &tr_mat):
        m_nb_diffuseTexture{tr_mat.m_nb_diffuseTexture},
        m_nb_specularTexture{tr_mat.m_nb_specularTexture},
        m_shininess{tr_mat.m_shininess},
        m_textures{tr_mat.m_textures},
        m_specular{tr_mat.m_specular},
        m_diffuse{tr_mat.m_diffuse},
        m_alpha{tr_mat.m_alpha},
        m_alpha_channel{tr_mat.m_alpha_channel}
    {}

    void addDiffuseMap(std::shared_ptr<Texture> t_diffuseTex);
    void addSpecularMap(std::shared_ptr<Texture> t_specularTex);
    void setSpecularVal(const glm::vec3 &tr_specularVal);
    void setDiffuseVal(const glm::vec3 &tr_diffuseVal);
    void setShininess(float t_shininess);
    void addToShader(Shader &t_shader);
    void setAlpha(float t_alpha);
    void setAlphaChannel(bool t_isRGBA);


private:
    std::vector<std::shared_ptr<Texture>> m_textures;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_alpha;
    int m_nb_diffuseTexture;
    int m_nb_specularTexture;
    float m_shininess;
    bool m_alpha_channel;
};


#endif //ENGINE_MATERIAL_H
