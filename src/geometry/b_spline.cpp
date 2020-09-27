//
// Created by Robin on 23/09/2020.
//

#include "b_spline.h"



BSpline::BSpline(): Model()
{
  _deg = 3;
  _nodalVector = std::vector<float>{1,2,3,4,5,6,7,8,9,10,11,12};
  _controlPoints = std::vector<glm::vec3>{
          glm::vec3(0, 0, 0), glm::vec3(1, 1, 0),
          glm::vec3(2, 1, 0),
          glm::vec3(3, 0, 0), glm::vec3(4, 0, 0), glm::vec3(5, 0, 0)
          , glm::vec3(7, 0, 0) , glm::vec3(8, 0, 0)
  };
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  GLuint indice = 0;
  for(float u = _nodalVector[_deg]; u < _nodalVector[_controlPoints.size()]; u +=0.5){
    Vertex v;
    v.Position = this->evaluate(u);
    vertices.push_back(v);
    indices.push_back(indice);
    indice++;
  }

  this->addMesh(std::make_shared<Mesh>(vertices, indices));
  vertices.clear();
  indices.clear();

}
BSpline::~BSpline(){}


glm::vec3 BSpline::evaluate(const float u)
{
  auto k =  _deg+1;
  auto i = k;
  auto dec = 0;
  while(u > _nodalVector[i])
  {
    i++;
    dec++;
  }

  auto tempPoints = std::vector<glm::vec3>(_controlPoints.begin()+dec, _controlPoints.begin()+dec+k-1);
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


void BSpline::drawModel(Shader shader)
{
  if(waitingToUpdate){
      waitingToUpdate=false;
      updateModel();
  }
  shader.use();
  shader.setMat4("model", getModel());
  shader.addMaterial(_material);
  for(auto &m : _meshs)
      m->drawLineMesh(shader);
}
