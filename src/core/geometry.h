//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "transform.h"
#include <vector>

/**
 * Vertex attributes
 */
struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    float weights[4];

    Vertex():
    position{glm::vec3(0,0,0)}
    ,normal{glm::vec3(1,1,1)}
    {}

    Vertex operator *(glm::mat4 transformMatrix){
        Vertex vec;
        vec.position = transformMatrix * glm::vec4(position,1);
        vec.normal = this->normal;
        vec.texCoords = this->texCoords;
        return vec;
    }

    bool operator==(const struct Vertex &v2) const {
        return position == v2.position;
    }

    Vertex operator *(float v2) const{
        Vertex vec;
        vec.position = this->position * glm::vec3(v2);
        vec.normal = this->normal;
        vec.texCoords = this->texCoords;
        return vec;
    }
    Vertex operator /(float v2) const{
        Vertex vec;
        vec.position = this->position/glm::vec3(v2);
        vec.normal = this->normal;
        vec.texCoords = this->texCoords;
        return vec;
    }
};






#endif //ENGINE_GEOMETRY_H
