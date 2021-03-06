//
// Created by Robin on 10/03/2020.
//

#include "material.h"


Material::Material() :
m_nb_specularTexture{0},
m_nb_diffuseTexture{0},
m_specular{glm::vec3(0.5f)},
m_diffuse{glm::vec3(0.5f)},
m_shininess{32.f},
m_alpha{1.f},
m_alpha_channel{false}
{

}

void Material::addDiffuseMap(std::shared_ptr<Texture> t_diffuseTex) {
    if(t_diffuseTex->isValid()){
        m_textures.emplace_back(std::move(t_diffuseTex));
        m_nb_diffuseTexture++;
    }

}

void Material::addSpecularMap(std::shared_ptr<Texture> t_specularTex) {
    if(t_specularTex->isValid()) {
        m_textures.emplace_back(t_specularTex);
        m_nb_specularTexture++;
    }
}

void Material::setSpecularVal(const glm::vec3 &tr_specularVal) {
    m_specular = tr_specularVal;
}

void Material::setDiffuseVal(const glm::vec3 &tr_diffuseVal) {
    m_diffuse = tr_diffuseVal;
}

void Material::setShininess(float t_shininess) {
    m_shininess = t_shininess;
}

void Material::addToShader(Shader &t_shader) {
    t_shader.setVec3("mat.diffuse", m_diffuse);
    t_shader.setVec3("mat.specular", m_specular);
    t_shader.setInt("mat.nb_diffuseMap", m_nb_diffuseTexture);
    t_shader.setInt("mat.nb_specularMap", m_nb_specularTexture);
    t_shader.setFloat("mat.shininess", m_shininess);
    t_shader.setFloat("mat.alpha",m_alpha);
    t_shader.setBool("mat.alphaChannel",m_alpha_channel);
    for(auto i =0; i < m_textures.size(); i++) {
        t_shader.setInt("mat."+m_textures[i]->getName(), i);
        m_textures[i]->bindToGL(t_shader, i);
    }
}

void Material::setAlpha(float t_alpha) {
    m_alpha =t_alpha;
}

void Material::setAlphaChannel(bool t_isRGBA) {
    m_alpha_channel = t_isRGBA;
}




