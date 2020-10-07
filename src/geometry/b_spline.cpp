//
// Created by Robin on 23/09/2020.
//

#include "b_spline.h"

#include <utility>


BSpline::BSpline(int deg, std::vector<glm::vec3> controlPoints, std::vector<float> nodalVector):
Model(),
_deg(deg),
_nodalVector(std::move(nodalVector)),
_controlPoints(std::move(controlPoints))
{

}
BSpline::~BSpline()= default;


glm::vec3 BSpline::evaluate(const float u)
{
  auto k =  _deg+1;
  auto i = k;
  int dec = 0;
  while(u > _nodalVector[i])
  {
    i++;
    dec++;
  }
  auto tempPoints = std::vector<glm::vec3>(_controlPoints.begin()+dec, _controlPoints.begin()+dec+k);
  for( auto l = 0; l < _deg; ++l )
  {
    for( auto j = 0; j < k - 1; j++)
    {

      tempPoints[j] = ( ( _nodalVector[dec+k+j] - u ) / (_nodalVector[dec+k+j] - _nodalVector[dec+1+j]) ) * tempPoints[j] +
              ( ( u - _nodalVector[dec+1+j] ) / (_nodalVector[dec+k+j] - _nodalVector[dec+1+j]) )* tempPoints[j+1];

    }
    dec++;
    k--;
  }


  return tempPoints[0];
}


