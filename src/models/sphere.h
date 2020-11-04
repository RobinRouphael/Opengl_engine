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
    Sphere(int t_nbStacks, int t_nbSectors);
    /**
     * Destructor
     */
    ~Sphere();

    /**
     * Set number of stacks
     * @param t_nbStacks
     */
    void setNbStacks(int t_nbStacks);
    /**
     * Set number of sectors
     * @param t_nbSectors
     */
    void setNbSectors(int t_nbSectors);
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
    int m_nb_sectors;
    int m_nb_stacks;
};


#endif //ENGINE_SPHERE_H
