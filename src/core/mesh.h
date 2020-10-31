//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include "geometry.h"
#include "texture.h"
#include <vector>
#include <memory>



class Mesh {
/**
 * Mesh with geometry, topology and textures
 */

public:
    /**
     * Constructor
     * @param t_vertices : geometry of mesh
     * @param t_indices : topology of mesh
     */
    Mesh(std::vector<Vertex> t_vertices, std::vector<GLuint> t_indices);


    /**
     * Constructor
     * @param t_vertices : geometry of mesh
     * @param t_indices : topology of mesh
     * @param t_textures : t_textures of mesh
     */
    Mesh(std::vector<Vertex> t_vertices, std::vector<GLuint> t_indices,
         const std::vector<std::shared_ptr<Texture>> &t_textures);

    /**
     * Destructor
     */
    ~Mesh();
    /**
     * Draw the mesh
     * @param tr_shader
     */
    void drawMesh(Shader &tr_shader, GLuint t_glmode);


    /**
     * Generate OpenGL buffers from geometry and topology
     */
    void generateMesh();
    /**
     * Add a texture
     * @param texture
     */

    void addTexture(std::shared_ptr<Texture> t_texture);


private:

    std::vector<Vertex> m_vertices;
    std::vector<GLuint > m_indices;
    std::vector<std::shared_ptr<Texture>> m_textures;

    // OpenGL object for models
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

};


#endif //ENGINE_MESH_H
