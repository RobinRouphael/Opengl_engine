//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_ASSET_H
#define ENGINE_ASSET_H
#include <utility>

#include "mesh.h"
#include "material.h"

class Asset {
    /**
     * Model of meshes with a Model Matrix
     */
public:
    enum class AssetType{Sphere, IcoSphere, Metaball, Custom};
    enum class ShaderType{OPAQUE,TRANSPARENT};
    /**
     * Constructor, do not create any Mesh,
     * it is the responsibility of the inherited classes
     * to create the meshes
     */
    Asset();

    virtual ~Asset();

    /**
     * Draws the model
     * @param tr_shader
     */
    void drawModel(Shader &tr_shader, GLuint t_glMode);


    /**
     * Adds a new Mesh to existing
     * @param t_mesh
     */
    void addMesh(std::shared_ptr<Mesh> t_mesh);



    /**
     * Update Model's meshes
     * inherited classes can reimplement this virtual function
     */
    virtual void updateModel();


    /**
     * Scale getter
     * @return scale vector
     */
    glm::vec3 getScale(){return m_scale;}
    /**
     * Scale setter
     * @param t_scale vector
     */
    void setScale(glm::vec3 t_scale){ m_scale = t_scale;}
    /**
     * Rotation getter
     * @return rotation vector
     */
    glm::vec3 getRotation(){return m_rotation;}
    /**
     * Rotation setter
     * @param t_rotation vector
     */
    void setRotation(glm::vec3 t_rotation){ m_rotation = t_rotation;}
    /**
     * Position getter
     * @return position vector
     */
    glm::vec3 getTranslation(){return m_translation;}
    /**
     * Position setter
     * @param t_position vector
     */
    void setTranslation(glm::vec3 t_position){ m_translation = t_position;}

    void setMaterial(std::shared_ptr<Material> t_mat){m_meshs[0]->setMaterial(std::move(t_mat));}
    void setDiffuseColor(const glm::vec4 &color){
        m_meshs[0]->getMaterial()->setDiffuseVal(glm::vec3(color.r,color.g,color.b));
        m_meshs[0]->getMaterial()->setAlpha(color.a);
    }
    glm::vec4 getDiffuseColor(){return glm::vec4(m_meshs[0]->getMaterial()->getDiffuseVal(),m_meshs[0]->getMaterial()->getAlpha());}

    AssetType getAssetType(){return m_asset_type;}

    void setAssetType(AssetType t_atype){m_asset_type=t_atype;}

    ShaderType getShaderType(){return m_shader_type;}

    void setShaderType(ShaderType t_stype){m_shader_type=t_stype;}

    const std::string &getName(){return m_name;}

    void setName(const std::string &tr_name){m_name=tr_name;}

    void setSelected(bool t_isSelected){m_selected=t_isSelected;}

    bool isSelected(){return m_selected;}

    void setToBeDestroyed(bool t_to_be_destroyed){m_to_be_destroyed=t_to_be_destroyed;}

    bool toBeDestroyed(){return m_to_be_destroyed;}


private:
    /**
     * Get Rotation Matrix
     * @return Rotation Matrix
     */
    glm::mat4 getRotationMatrix(){
        glm::vec3 x{1.f, 0.f, 0.f};
        glm::vec3 y{0.f, 1.f, 0.f};
        glm::vec3 z{0.f, 0.f, 1.f};
        glm::mat4 rot = glm::rotate(glm::mat4(), glm::radians(m_rotation.x), x);
        rot = glm::rotate(rot, glm::radians(m_rotation.y), y);
        rot = glm::rotate(rot, glm::radians(m_rotation.z), z);
        return rot;
    }


protected:

    /**
     * Get Model Matrix
     * @return Translation Mat * Rotation Mat * Scale Mat
     */
    glm::mat4 getModel(){
        return glm::translate(glm::mat4(), m_translation)
               * getRotationMatrix()
               *glm::scale(glm::mat4(), m_scale);
    }

    [[nodiscard]] std::vector<std::shared_ptr<Mesh>> getMeshs() const {return m_meshs;}

    void setMeshs(const std::vector<std::shared_ptr<Mesh>> &t_meshs){m_meshs = t_meshs;}

    void setWaitingToUpdate(bool t_waitingToUpdate){ m_waiting_to_update = t_waitingToUpdate;}


private:
    glm::vec3 m_scale;
    glm::vec3 m_translation;
    glm::vec3 m_rotation;
    AssetType m_asset_type{AssetType::Custom};
    ShaderType m_shader_type{ShaderType::OPAQUE};
    bool m_waiting_to_update;
    bool m_to_be_destroyed{false};
    bool m_selected{false};
    std::vector<std::shared_ptr<Mesh>> m_meshs;
    std::string m_name;
};


#endif //ENGINE_ASSET_H
