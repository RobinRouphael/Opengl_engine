//
// Created by Robin on 22/02/2020.
//

#ifndef ENGINE_SPHERE_H
#define ENGINE_SPHERE_H
#include "core/model.h"
class Sphere : public Model{
    /**
     * UV Sphere
     */
public:
    /**
     * Constructor
     * Create UV Sphere in a single Mesh
     */
    Sphere();
    /**
     * Destructor
     */
    ~Sphere();

    /**
     * Set number of stacks
     * @param nbStacks
     */
    void setNbStacks(int nbStacks);
    /**
     * Set number of sectors
     * @param nbSectors
     */
    void setNbSectors(int nbSectors);
    /**
     * Get number of stacks
     * @return
     */
    int getNBStacks();
    /**
     * Get number of sectors
     * @return
     */
    int getNBSectors();
    /**
     * Reset Mesh from a new number of sectors or stacks
     */
    void updateModel() override;
    /**
     * Set a diffuse map
     * @param texture
     */
    void setTextureDiffuse(const std::shared_ptr<Texture> &texture);


private:
    /**
     * Create vertices
     * @return
     */
    std::vector<Vertex> createVertices();
    /**
     * Create indices from vertices
     * @return
     */
    std::vector<GLuint> createIndices() ;

private:
    int _nbSectors;
    int _nbStacks;
    std::shared_ptr<Texture> _textureDiffuse;
};


#endif //ENGINE_SPHERE_H
