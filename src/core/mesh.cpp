//
// Created by Robin on 22/02/2020.
//

#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, const std::vector<std::shared_ptr<Texture>> &textures):
        vertices_(std::move(vertices)),
        indices_(std::move(indices)),
        textures_(textures)
{
    generateMesh();

}



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices):
        Mesh(std::move(vertices), std::move(indices), std::vector<std::shared_ptr<Texture>>())
{
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    glDeleteVertexArrays(1, &vao_) ;
}


void Mesh::drawMesh(Shader &shader, GLuint glmode)
{
    shader.isTextured(!textures_.empty());

    for(auto i =0; i < textures_.size(); i++)
        textures_[i]->bindToGL(shader, i);

    glBindVertexArray(vao_);
    glDrawElements(glmode, indices_.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}



void Mesh::generateMesh()
{

    // Initialize the models
    // 1. Generate models buffers
    glGenBuffers(1, &vbo_) ;
    glGenBuffers(1, &ebo_) ;
    glGenVertexArrays(1, &vao_) ;
    // 2. Bind Vertex Array Object
    glBindVertexArray(vao_);

    // 3. Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof (Vertex), vertices_.data(), GL_STATIC_DRAW);

    // vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // normal attributes pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    // texture attributes pointers
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    // 7. Copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof (GLfloat), indices_.data(), GL_STATIC_DRAW);
    //6. Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::addTexture(std::shared_ptr<Texture> t) {
    textures_.emplace_back(t);

}


