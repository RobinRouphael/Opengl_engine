//
// Created by robin on 29/09/2020.
//

#ifndef ENGINE_BSPLINESURFACE_H
#define ENGINE_BSPLINESURFACE_H

#include "bSpline.h"
class BSplineSurface : public Model{
    /**
 *
 */
public:
    /**
     * Constructor
     */
    BSplineSurface(int t_deg, float t_step, std::vector<float> t_nodalVectorV, std::vector<float> t_nodalVectorU,
                   const std::vector<std::vector<glm::vec3>>& t_uSplinesPoints);
    /**
     * Destructor
     */
    ~BSplineSurface() override;

private:
    void createBSplineSurface();

private:
    int m_deg;
    float m_step;

    std::vector<float> m_nodal_vector_v; ///Nodal vector to compute v
    std::vector<float> m_nodal_vector_u; ///Nodal vector to compute u
    std::shared_ptr<BSpline> m_v_spline; ///Generator bspline in v
    std::vector<std::shared_ptr<BSpline>> m_u_splines; ///Direction bsplines in u
};


#endif //ENGINE_BSPLINESURFACE_H
