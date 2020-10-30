//
// Created by Robin on 23/09/2020.
//

#include "bSpline.h"

#include <utility>


BSpline::BSpline(int deg, std::vector<glm::vec3> controlPoints, std::vector<float> nodalVector):
        Model(),
        deg_(deg),
        nodal_vector(std::move(nodalVector)),
        control_points(std::move(controlPoints))
{

}
BSpline::BSpline(int deg, std::vector<glm::vec3> controlPoints, std::vector<float> nodalVector, float step):
        Model(),
        deg_(deg),
        nodal_vector(std::move(nodalVector)),
        control_points(std::move(controlPoints)),
        step_(step)
{
    createBSpline();
}


BSpline::~BSpline()= default;


glm::vec3 BSpline::evaluate(const float u)
{
  auto k = deg_ + 1;
  auto i = k;
  int dec = 0;
  while(u > nodal_vector[i])
  {
    i++;
    dec++;
  }
  auto tempPoints = std::vector<glm::vec3>(control_points.begin() + dec, control_points.begin() + dec + k);
  for(auto l = 0; l < deg_; ++l )
  {
    for( auto j = 0; j < k - 1; j++)
    {

      tempPoints[j] = ((nodal_vector[dec + k + j] - u ) / (nodal_vector[dec + k + j] - nodal_vector[dec + 1 + j]) ) * tempPoints[j] +
                      ((u - nodal_vector[dec + 1 + j] ) / (nodal_vector[dec + k + j] - nodal_vector[dec + 1 + j]) ) * tempPoints[j + 1];

    }
    dec++;
    k--;
  }


  return tempPoints[0];
}

void BSpline::createBSpline() {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    int index = 0;
    for(int u = nodal_vector[deg_] / step_; u < nodal_vector[nodal_vector.size() - deg_ - 1] / step_; u +=1 ) {
        ///Compute for all u
        Vertex vertex;
        vertex.Position = evaluate(u * step_);
        vertices.push_back(vertex);
        indices.emplace_back(index++);
    }

    this->addMesh(std::make_shared<Mesh>(vertices, indices));
    vertices.clear();
    indices.clear();
}








