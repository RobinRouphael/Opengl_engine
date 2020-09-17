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
     * @param shader
     */
    void drawModel(Shader shader);


    /**
     * Adds a new Mesh to existing
     * @param mesh
     */
    void addMesh(std::shared_ptr<Mesh> mesh);



    /**
     * Update Model's meshes
     * inherited classes can reimplement this virtual function
     */
    virtual void updateModel();


    /**
     * Scale getter
     * @return scale vector
     */
    glm::vec3 getScale(){return _scale;}
    /**
     * Scale setter
     * @param scale vector
     */
    void setScale(glm::vec3 scale){_scale = scale;}
    /**
     * Rotation getter
     * @return rotation vector
     */
    glm::vec3 getRotation(){return _rotation;}
    /**
     * Rotation setter
     * @param rotation vector
     */
    void setRotation(glm::vec3 rotation){_rotation = rotation;}
    /**
     * Position getter
     * @return position vector
     */
    glm::vec3 getPosition(){return _translation;}
    /**
     * Position setter
     * @param position vector
     */
    void setPosition(glm::vec3 position){_translation = position;}


private:
    /**
     * Get Rotation Matrix
     * @return Rotation Matrix
     */
    glm::mat4 getRotationMatrix(){
        glm::vec3 x{1.f, 0.f, 0.f};
        glm::vec3 y{0.f, 1.f, 0.f};
        glm::vec3 z{0.f, 0.f, 1.f};
        glm::mat4 rot = glm::rotate(glm::mat4(),glm::radians(_rotation.x), x);
        rot = glm::rotate(rot,glm::radians(_rotation.y),y);
        rot = glm::rotate(rot, glm::radians(_rotation.z),z);
        return rot;
    }

    /**
     * Get Model Matrix
     * @return Translation Mat * Rotation Mat * Scale Mat
     */
    glm::mat4 getModel(){
        return glm::translate(glm::mat4(),_translation)
               * getRotationMatrix()
               *glm::scale(glm::mat4(),_scale);
    }



private:
    Material _material;

protected:
    std::vector<std::shared_ptr<Mesh>> _meshs;
    glm::vec3 _scale;
    glm::vec3 _translation;
    glm::vec3 _rotation;
    bool waitingToUpdate;

};


#endif //ENGINE_MODEL_H
