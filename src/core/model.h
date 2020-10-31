//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H
#include "mesh.h"
#include "material.h"

class Model {
    /**
     * Model of meshes with a Model Matrix
     */
public:
    /**
     * Constructor, do not create any Mesh,
     * it is the responsibility of the inherited classes
     * to create the meshes
     */
    Model();

    virtual ~Model();

    /**
     * Draws the model
     * @param tr_shader
     */
    void drawModel(Shader &tr_shader, GLuint t_glmode);


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

    void setMaterial(const Material &t_material){m_material = t_material;}

protected: //TODO : set this to private
    std::vector<std::shared_ptr<Mesh>> m_meshs;
    bool m_waiting_to_update;
    Material m_material;

private:
    glm::vec3 m_scale;
    glm::vec3 m_translation;
    glm::vec3 m_rotation;
};


#endif //ENGINE_MODEL_H
