//
// Created by robin on 29/09/2020.
//

#include "bSplineSurface.h"

#include <utility>

BSplineSurface::BSplineSurface(int t_deg, float t_step, std::vector<float> t_nodalVectorV, std::vector<float> t_nodalVectorU,
                               const std::vector<std::vector<glm::vec3>>& t_uSplinesPoints):
        Model(),
        m_deg(t_deg),
        m_step(t_step),
        m_nodal_vector_v(std::move(t_nodalVectorV)),
        m_nodal_vector_u(std::move(t_nodalVectorU))
                     {
    ///Creation of directionnal u_splines
    for(auto &spline : t_uSplinesPoints)
        m_u_splines.emplace_back(std::make_shared<BSpline>(m_deg, spline, m_nodal_vector_u));
    ///Compute on u and v
    createBSplineSurface();

}

BSplineSurface::~BSplineSurface() = default;

void BSplineSurface::createBSplineSurface() {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
   ///For all u
    for(int u = m_nodal_vector_u[m_deg] / m_step; u < m_nodal_vector_u[m_nodal_vector_u.size() - m_deg - 1] / m_step; u +=1 ){

        std::vector<glm::vec3> uControlPoints;
        ///Compute dj(u) for all directional u splines
        for(auto &uspline : m_u_splines)
            //Store the result to be used as the control polygon for the v spline
            uControlPoints.emplace_back(uspline->evaluate(u * m_step));

        ///Create v_spline
        m_v_spline = std::make_shared<BSpline>(m_deg, uControlPoints, m_nodal_vector_v);
        ///Compute for all v
        for(int v = m_nodal_vector_v[m_deg] / m_step; v < m_nodal_vector_v[m_nodal_vector_v.size() - m_deg - 1] / m_step; v +=1 ) {
            Vertex vertex;
            vertex.position = m_v_spline->evaluate(v * m_step);
            vertex.normal = glm::vec3{0};
            vertex.texCoords = glm::vec2(float(v)/m_nodal_vector_v[m_nodal_vector_v.size() - m_deg - 1],float(u)/m_nodal_vector_u[m_nodal_vector_u.size() - m_deg - 1] );
            vertices.push_back(vertex);

        }
        uControlPoints.clear();
    }
    ///Topology
    ///Simple meshing algorithm for a plane + normals
    int vStep = (m_nodal_vector_v[m_nodal_vector_v.size() - m_deg - 1] - m_nodal_vector_v[m_deg]) / m_step ;
    int uStep = (m_nodal_vector_u[m_nodal_vector_u.size() - m_deg - 1] - m_nodal_vector_u[m_deg]) / m_step ;
    int k1, k2, k3;
    glm::vec3 edgeAB, edgeAC, areaWeightedNormal;
    for(int u = 0; u < uStep-1; u ++){
        for(int v = 0; v < vStep-1; v++){

            k1 = u * vStep + v;
            k2 = u * vStep + 1 + v;
            k3 = (u+1) * vStep + v;
            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);

            edgeAB = vertices[k2].position - vertices[k1].position;
            edgeAC = vertices[k3].position - vertices[k1].position;
            areaWeightedNormal = glm::cross(edgeAB, edgeAC);
            vertices[k1].normal += areaWeightedNormal;
            vertices[k2].normal += areaWeightedNormal;
            vertices[k3].normal += areaWeightedNormal;

            k1 = k3;
            k3 = (u+1) * vStep + v + 1;

            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);
            edgeAB = vertices[k2].position - vertices[k1].position;
            edgeAC = vertices[k3].position - vertices[k1].position;
            areaWeightedNormal = glm::cross(edgeAB, edgeAC);
            vertices[k1].normal += areaWeightedNormal;
            vertices[k2].normal += areaWeightedNormal;
            vertices[k3].normal += areaWeightedNormal;
        }

    }

    for(auto & vertice : vertices)
        glm::normalize(vertice.normal);

    this->addMesh(std::make_shared<Mesh>(vertices, indices,std::make_shared<Material>()));
    vertices.clear();
    indices.clear();
}



