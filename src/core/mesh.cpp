//
// Created by Robin on 22/02/2020.
//

#include "mesh.h"


Mesh::Mesh(std::vector<Vertex> t_vertices, std::vector<GLuint> t_indices, const std::vector<std::shared_ptr<Texture>> &t_textures):
        m_vertices(std::move(t_vertices)),
        m_indices(std::move(t_indices)),
        m_textures(t_textures)
{
    generateMesh();

}



Mesh::Mesh(std::vector<Vertex> t_vertices, std::vector<GLuint> t_indices):
        Mesh(std::move(t_vertices), std::move(t_indices), std::vector<std::shared_ptr<Texture>>())
{
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao) ;
}


void Mesh::drawMesh(Shader &tr_shader, GLuint t_glmode)
{
    tr_shader.isTextured(!m_textures.empty());

    for(auto i =0; i < m_textures.size(); i++)
        m_textures[i]->bindToGL(tr_shader, i);

    glBindVertexArray(m_vao);
    glDrawElements(t_glmode, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}



void Mesh::generateMesh()
{

    // Initialize the models
    // 1. Generate models buffers
    glGenBuffers(1, &m_vbo) ;
    glGenBuffers(1, &m_ebo) ;
    glGenVertexArrays(1, &m_vao) ;
    // 2. Bind Vertex Array Object
    glBindVertexArray(m_vao);

    // 3. Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof (Vertex), m_vertices.data(), GL_STATIC_DRAW);

    // vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // normal attributes pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // texture attributes pointers
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    // 7. Copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof (GLfloat), m_indices.data(), GL_STATIC_DRAW);
    //6. Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::addTexture(std::shared_ptr<Texture> t_texture) {
    m_textures.emplace_back(t_texture);

}


