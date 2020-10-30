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
     * Constructor without computation
     */
    BSpline(int deg,std::vector<glm::vec3> controlPoints,std::vector<float> nodalVector);
    /**
     * Constructor with computation
     */
    BSpline(int deg,std::vector<glm::vec3> controlPoints,std::vector<float> nodalVector, float step);
    /**
     * Destructor
     */
    ~BSpline() override;

    glm::vec3 evaluate(float u);


private:
    void createBSpline();

private:
    int deg_;
    float step_;
    std::vector<float> nodal_vector;
    std::vector<glm::vec3> control_points;

};
