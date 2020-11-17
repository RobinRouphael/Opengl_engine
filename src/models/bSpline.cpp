//
// Created by Robin on 23/09/2020.
//

#include "bSpline.h"

#include <utility>


BSpline::BSpline(int t_deg, std::vector<glm::vec3> t_controlPoints, std::vector<float> t_nodalVector):
        Asset(),
        m_deg(t_deg),
        m_nodal_vector(std::move(t_nodalVector)),
        m_control_points(std::move(t_controlPoints))
{

}
BSpline::BSpline(int t_deg, std::vector<glm::vec3> t_controlPoints, std::vector<float> t_nodalVector, float t_step):
        Asset(),
        m_deg(t_deg),
        m_nodal_vector(std::move(t_nodalVector)),
        m_control_points(std::move(t_controlPoints)),
        m_step(t_step)
{
    createBSpline();
}


BSpline::~BSpline()= default;


glm::vec3 BSpline::evaluate(const float t_u)
{
  auto k = m_deg + 1;
  auto i = k;
  int dec = 0;
  while(t_u > m_nodal_vector[i])
  {
    i++;
    dec++;
  }
  auto tempPoints = std::vector<glm::vec3>(m_control_points.begin() + dec, m_control_points.begin() + dec + k);
  for(auto l = 0; l < m_deg; ++l )
  {
    for( auto j = 0; j < k - 1; j++)
    {

      tempPoints[j] = ((m_nodal_vector[dec + k + j] - t_u ) / (m_nodal_vector[dec + k + j] - m_nodal_vector[dec + 1 + j]) ) * tempPoints[j] +
                      ((t_u - m_nodal_vector[dec + 1 + j] ) / (m_nodal_vector[dec + k + j] - m_nodal_vector[dec + 1 + j]) ) * tempPoints[j + 1];

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
    for(int u = m_nodal_vector[m_deg] / m_step; u < m_nodal_vector[m_nodal_vector.size() - m_deg - 1] / m_step; u +=1 ) {
        ///Compute for all u
        Vertex vertex;
        vertex.position = evaluate(u * m_step);
        vertices.push_back(vertex);
        indices.emplace_back(index++);
    }

    this->addMesh(std::make_shared<Mesh>(vertices, indices,std::make_shared<Material>()));
    vertices.clear();
    indices.clear();
}








