//
// Created by Robin on 15/03/2020.
//

#ifndef ENGINE_CUBE_H
#define ENGINE_CUBE_H


#include <src/core/asset.h>

class Cube : public Asset{
    /**
     * Simple Cube
     */
public:
    /**
     * Constructor
     * Create a Mesh per face
     */
    Cube();
    /**
     * Destructor
     */
    ~Cube();
private:
    /**
     *
     */
    void setup();


private:
    int m_resolution;

};


#endif //ENGINE_CUBE_H
