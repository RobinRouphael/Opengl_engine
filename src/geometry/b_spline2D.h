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
    BSpline2D();
    /**
     * Destructor
     */
    ~BSpline2D();

    void drawModel(Shader shader) override;

private:
    glm::vec3 evaluate(const std::vector<glm::vec3> &uControlPoints, float v);
private:
    int _deg;
    float _step;
    std::vector<float> _nodalVectorV;
    std::vector<float> _nodalVectorU;
    std::vector<std::shared_ptr<BSpline>> _uSplines;
};


#endif //ENGINE_B_SPLINE2D_H
