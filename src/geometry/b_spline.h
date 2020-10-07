//
// Created by Robin on 23/09/2020.
//

#ifndef ENGINE_BSPLINE_H
#define ENGINE_BSPLINE_H

#endif //ENGINE_BSPLINE_H


#include <src/core/model.h>
#include "models/sphere.h"
class BSpline : public Model{
    /**
     *
     */
public:
    /**
     * Constructor
     */
    BSpline(int deg,std::vector<glm::vec3> controlPoints,std::vector<float> nodalVector);
    /**
     * Destructor
     */
    ~BSpline() override;

    glm::vec3 evaluate(float u);


private:
    int _deg;
    std::vector<float> _nodalVector;
    std::vector<glm::vec3> _controlPoints;

};
