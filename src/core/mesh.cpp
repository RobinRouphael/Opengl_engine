//
// Created by Robin on 22/02/2020.
//

#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, const std::vector<std::shared_ptr<Texture>> &textures):
        _vertices(std::move(vertices)),
        _indices(std::move(indices)),
        _textures(textures)
{
    generateMesh();

}



Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices):
        Mesh(std::move(vertices), std::move(indices), std::vector<std::shared_ptr<Texture>>())
{
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao) ;
}


void Mesh::drawMesh(Shader &shader, GLuint glmode)
{
    shader.isTextured(!_textures.empty());

    for(auto i =0; i< _textures.size();i++)
        _textures[i]->bindToGL(shader,i);

    glBindVertexArray(_vao);
    glDrawElements(glmode, _indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}



void Mesh::generateMesh()
{

    // Initialize the models
    // 1. Generate models buffers
    glGenBuffers(1, &_vbo) ;
    glGenBuffers(1, &_ebo) ;
    glGenVertexArrays(1, &_vao) ;
    // 2. Bind Vertex Array Object
    glBindVertexArray(_vao);

    // 3. Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof (Vertex), _vertices.data(), GL_STATIC_DRAW);

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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof (GLfloat), _indices.data(), GL_STATIC_DRAW);
    //6. Unbind the VAO
    glBindVertexArray(0);
}


