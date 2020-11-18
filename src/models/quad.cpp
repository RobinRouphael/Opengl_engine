//
// Created by robin on 23/10/2020.
//

#include "quad.h"

ScreenQuad::ScreenQuad(float t_x, float t_y, float t_width, float t_height):
        Asset(),
        m_x(t_x),
        m_y(t_y),
        m_width(t_width),
        m_height(t_height)
{
    setAssetType(AssetType::Custom);
    setup();
}

void ScreenQuad::setup(){
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices= {0, 1, 2, 0, 2, 3};
    Vertex v;
    v.position = glm::vec3(m_x, m_y, 0.f);
    v.texCoords = glm::vec2(0.f, 1.f);
    v.normal = glm::vec3(0,0,1);
    vertices.push_back(v);
    v.position = glm::vec3(m_x + m_width, m_y, 0.f);
    v.texCoords = glm::vec2(1.f, 1.f);
    v.normal = glm::vec3(0,0,1);
    vertices.push_back(v);
    v.position = glm::vec3(m_x + m_width, m_y - m_height, 0.f);
    v.texCoords = glm::vec2(1.f, 0.f);
    v.normal = glm::vec3(0,0,1);
    vertices.push_back(v);
    v.position = glm::vec3(m_x, m_y - m_height, 0.f);
    v.texCoords = glm::vec2(0.f, 0.f);
    v.normal = glm::vec3(0,0,1);
    vertices.push_back(v);

    addMesh(std::make_shared<Mesh>(vertices, indices,std::make_shared<Material>()));
    vertices.clear();
    indices.clear();

}
