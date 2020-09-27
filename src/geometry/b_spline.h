//
// Created by Robin on 23/09/2020.
//

#ifndef ENGINE_BSPLINE_H
#define ENGINE_BSPLINE_H

#endif //ENGINE_BSPLINE_H


#include <src/core/model.h>

class BSpline : public Model{
    /**
     *
     */
public:
    /**
     * Constructor
     */
    BSpline();
    /**
     * Destructor
     */
    ~BSpline();

    void drawModel(Shader shader) override;

private:
  glm::vec3 evaluate(float u);


private:
    int _deg;
    std::vector<float> _nodalVector;
    std::vector<glm::vec3> _controlPoints;


};
