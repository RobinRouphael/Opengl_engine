//
// Created by robin on 29/09/2020.
//

#ifndef ENGINE_B_SPLINE2D_H
#define ENGINE_B_SPLINE2D_H

#include "b_spline.h"
class BSpline2D : public Model{
    /**
 *
 */
public:
    /**
     * Constructor
     */
    BSpline2D(int deg, float step, std::vector<float> nodalVectorV, std::vector<float> nodalVectorU,
              const std::vector<std::vector<glm::vec3>>& uSplinesPoints);
    /**
     * Destructor
     */
    ~BSpline2D() override;

private:
    void createBSpline2D();

private:
    int _deg;
    float _step;
    std::vector<float> _nodalVectorV;
    std::vector<float> _nodalVectorU;
    std::shared_ptr<BSpline> _vSpline;
    std::vector<std::shared_ptr<BSpline>> _uSplines;
};


#endif //ENGINE_B_SPLINE2D_H
