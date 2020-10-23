//
// Created by robin on 23/10/2020.
//

#include "quad.h"

ScreenQuad::ScreenQuad(float x, float y, float width, float height):
    Model(),
    x_(x),
    y_(y),
    width_(width),
    height_(height)
{
    setup();
}

void ScreenQuad::setup(){

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices= {0, 1, 2, 0, 2, 3};
    Vertex v;
    v.Position = glm::vec3(x_, y_, 0.f);
    v.TexCoords = glm::vec2(0.f, 1.f);
    vertices.push_back(v);
    v.Position = glm::vec3(x_ + width_, y_, 0.f);
    v.TexCoords = glm::vec2(1.f, 1.f);
    vertices.push_back(v);
    v.Position = glm::vec3(x_ + width_, y_ - height_, 0.f);
    v.TexCoords = glm::vec2(1.f, 0.f);
    vertices.push_back(v);
    v.Position = glm::vec3(x_, y_ - height_, 0.f);
    v.TexCoords = glm::vec2(0.f, 0.f);
    vertices.push_back(v);

    addMesh(std::make_shared<Mesh>(vertices, indices));
    vertices.clear();
    indices.clear();

}

void ScreenQuad::addTexture(std::shared_ptr<Texture> t) {
    _meshs[0]->addTexture(t);

}
