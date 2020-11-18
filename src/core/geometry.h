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
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    bool operator==(const struct Vertex &v2) const {
        return position == v2.position;
    }
};






#endif //ENGINE_GEOMETRY_H
