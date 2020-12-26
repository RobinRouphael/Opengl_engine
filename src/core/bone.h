//
// Created by robin on 24/12/2020.
//

#ifndef ENGINE_BONE_H
#define ENGINE_BONE_H


#include <vector>
#include <iostream>
#include "transform.h"
#include "shader.h"

class Bone {
public:
    Bone(glm::vec3 t_position_1, glm::vec3 t_position_2,std::vector<Vertex> &t_vertices,int t_boneID):
    m_position_1(t_position_1)
    ,m_position_2(t_position_2)
    ,m_id(t_boneID)
    {
        /// for each vertices, the weight of this bone is computed using the smallest distance between their position
        /// and the segment defined by the two articulations of the bone
        for(auto &v : t_vertices){
            float dist = computePointDistance(v.position);
            float weight = 1.f/dist;
            v.weights[t_boneID] = weight;
        }

    };
    ~Bone()=default;

    /**
     * Compute transformation on CPU
     * @param tr_vertex
     * @return
     */
    Vertex computeAnimation(Vertex &tr_vertex) const {
        return tr_vertex * m_transform.getTransform();
    }
    /**
     * Transform setter
     * @param t_transform
     */
    void setTransform(const Transform &t_transform){
        m_transform = t_transform;
    }
    /**
     * Rotation matrix of the transform getter
     * @return
     */
    glm::vec3 getTransformRot(){
        return m_transform.getRotation();
    }
    /**
     * Add bone to the vertex shader for GPU animation
     * @param tr_shader
     */
    void addToShader(Shader &tr_shader){
        tr_shader.setMat4("bones[" + std::to_string(m_id) + "].transform", m_transform.getTransform());
    }

private:
    /**
     * Compute the smallest distance between a point and the segment defined by the two extremities of the bone
     * @param t_vertexPosition
     * @return
     */
    float computePointDistance(glm::vec3 t_vertexPosition){
        auto ab = m_position_2 - m_position_1;
        auto be = t_vertexPosition - m_position_2;
        auto ae = t_vertexPosition - m_position_1;
        auto abbe = glm::dot(ab, be);
        auto abae = glm::dot(ab,ae);
        if(abbe > 0){
            return glm::length(be);
        }
        if(abae < 0){
            return glm::length((ae));
        }
        auto area = glm::length(glm::cross(ab, ae));
        return area / glm::length(ab);

    }
private:
    glm::vec3 m_position_1; //First position
    glm::vec3 m_position_2; //Second position
    int m_id; //ID
    Transform m_transform; //Transformation;
};


#endif //ENGINE_BONE_H
