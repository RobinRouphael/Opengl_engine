//
// Created by Robin on 01/03/2020.
//

#ifndef ENGINE_ICOSPHERE_H
#define ENGINE_ICOSPHERE_H
#include "core/asset.h"

class Icosphere  : public Asset{
    /**
     * Icosphere created from the subdivisions of the triangles of an icosahedron
     */
public:
    /**
     * Constructor
     * Create base Icosahedron and its subdivisions
     */
    Icosphere();
    /**
     * Destructor
     */
    ~Icosphere();
    /**
     * Set number of subdivisions
     * @param t_nbSubdiv
     */
    void setNBSubdivisions(int t_nbSubdiv);
    /**
     * Getter of number of subdivisons
     * @return
     */
    int getNBSubdivisions();

    /**
     * Reset the meshes with a new number of subdivisions
     */
    void updateModel() override;


private:
    /**
     * Create the original Icosahedron
     */
    void createIcosahedron();
    /**
     * Subdivise the triangles of the Icosahedron
     */
    void createSubdivisions();

    static GLuint mod_eq(GLuint a, GLuint b)
    {
        return (a == b ? a : a%b);
    }



private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    int m_nb_subdivisions;

};


#endif //ENGINE_ICOSPHERE_H
