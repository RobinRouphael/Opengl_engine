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
    BSpline(int t_deg, std::vector<glm::vec3> t_controlPoints, std::vector<float> t_nodalVector);
    /**
     * Constructor with computation
     */
    BSpline(int t_deg, std::vector<glm::vec3> t_controlPoints, std::vector<float> t_nodalVector, float t_step);
    /**
     * Destructor
     */
    ~BSpline() override;

    glm::vec3 evaluate(float t_u);


private:
    void createBSpline();

private:
    int m_deg;
    float m_step;
    std::vector<float> m_nodal_vector;
    std::vector<glm::vec3> m_control_points;

};
