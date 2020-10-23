//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_GEOMETRY_H
#define ENGINE_GEOMETRY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/**
 * Vertex attributes
 */
struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};



#endif //ENGINE_GEOMETRY_H
