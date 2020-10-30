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
    BSplineSurface(int deg, float step, std::vector<float> nodalVectorV, std::vector<float> nodalVectorU,
                   const std::vector<std::vector<glm::vec3>>& uSplinesPoints);
    /**
     * Destructor
     */
    ~BSplineSurface() override;

private:
    void createBSplineSurface();

private:
    int deg_;
    float step_;

    std::vector<float> nodal_vector_v; ///Nodal vector to compute v
    std::vector<float> nodal_vector_u; ///Nodal vector to compute u
    std::shared_ptr<BSpline> v_spline; ///Generator bspline in v
    std::vector<std::shared_ptr<BSpline>> u_splines; ///Direction bsplines in u
};


#endif //ENGINE_BSPLINESURFACE_H
