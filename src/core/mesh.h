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
     * @param vertices : geometry of mesh
     * @param indices : topology of mesh
     */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);


    /**
     * Constructor
     * @param vertices : geometry of mesh
     * @param indices : topology of mesh
     * @param textures : textures of mesh
     */
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
         const std::vector<std::shared_ptr<Texture>> &textures);

    /**
     * Destructor
     */
    ~Mesh();
    /**
     * Draw the mesh
     * @param shader
     */
    void drawMesh(Shader &shader, GLuint glmode);


    /**
     * Generate OpenGL buffers from geometry and topology
     */
    void generateMesh();
    /**
     * Add a texture
     * @param texture
     */

    void addTexture(std::shared_ptr<Texture> t);


private:

    std::vector<Vertex> vertices_;
    std::vector<GLuint > indices_;
    std::vector<std::shared_ptr<Texture>> textures_;

    // OpenGL object for models
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;

};


#endif //ENGINE_MESH_H
