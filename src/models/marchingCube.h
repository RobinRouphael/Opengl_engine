//
// Created by robin on 09/11/2020.
//

#ifndef ENGINE_MARCHINGCUBE_H
#define ENGINE_MARCHINGCUBE_H

#include <array>
#include <src/core/geometry.h>
#include <vector>
#include <src/core/mesh.h>
#include <functional>
#include "opengl_stuff.h"

class MarchingCube {
public:
    struct Cube{
        std::array<glm::vec3,8> points;
        std::array<float,8> values;
    };

    MarchingCube():
        m_grid_size{10},
        m_cube_size{0.08f},
        m_iso_level{1.f}
        {};

    ~MarchingCube() = default;

    void setCubeSize(float t_size){m_cube_size=t_size;}
    void setIsoLevel(float t_level){m_iso_level=t_level;}
    float getIsoLevel(){
        return m_iso_level;
    }
    float getCubeSize(){
        return m_cube_size;
    }

    void polygonise(Cube &tr_cube, std::vector<Vertex> &tr_vertices,std::vector<GLuint> &tr_indices);
    std::shared_ptr<Mesh> generateMesh(const std::function<float(glm::vec3)> &tr_iso_function);
private:
    [[nodiscard]] glm::vec3 vertexInterp(glm::vec3 p1, glm::vec3 p2, float v1, float v2) const;
private:
    int m_grid_size;
    float m_cube_size;
    float m_iso_level;
    static int m_edge_table[256];
    static int m_tri_table[256][16];

};


#endif //ENGINE_MARCHINGCUBE_H
