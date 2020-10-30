//
// Created by robin on 29/09/2020.
//

#include "bSplineSurface.h"

#include <utility>

BSplineSurface::BSplineSurface(int deg, float step, std::vector<float> nodalVectorV, std::vector<float> nodalVectorU,
                               const std::vector<std::vector<glm::vec3>>& uSplinesPoints):
        Model(),
        deg_(deg),
        step_(step),
        nodal_vector_v(std::move(nodalVectorV)),
        nodal_vector_u(std::move(nodalVectorU))
                     {
    ///Creation of directionnal u_splines
    for(auto &spline : uSplinesPoints)
        u_splines.emplace_back(std::make_shared<BSpline>(deg_, spline, nodal_vector_u));
    ///Compute on u and v
    createBSplineSurface();

}

BSplineSurface::~BSplineSurface() = default;

void BSplineSurface::createBSplineSurface() {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
   ///For all u
    for(int u = nodal_vector_u[deg_] / step_; u < nodal_vector_u[nodal_vector_u.size() - deg_ - 1] / step_; u +=1 ){

        std::vector<glm::vec3> uControlPoints;
        ///Compute dj(u) for all directional u splines
        for(auto &uspline : u_splines)
            //Store the result to be used as the control polygon for the v spline
            uControlPoints.emplace_back(uspline->evaluate(u * step_));

        ///Create v_spline
        v_spline = std::make_shared<BSpline>(deg_, uControlPoints, nodal_vector_v);
        ///Compute for all v
        for(int v = nodal_vector_v[deg_] / step_; v < nodal_vector_v[nodal_vector_v.size() - deg_ - 1] / step_; v +=1 ) {
            Vertex vertex;
            vertex.Position = v_spline->evaluate(v * step_);
            vertex.Normal = glm::vec3{0};
            vertices.push_back(vertex);

        }
        uControlPoints.clear();
    }
    ///Topology
    ///Simple meshing algorithm for a plane + normals
    int vStep = (nodal_vector_v[nodal_vector_v.size() - deg_ - 1] - nodal_vector_v[deg_]) / step_ ;
    int uStep = (nodal_vector_u[nodal_vector_u.size() - deg_ - 1] - nodal_vector_u[deg_]) / step_ ;
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

            edgeAB = vertices[k2].Position - vertices[k1].Position;
            edgeAC = vertices[k3].Position - vertices[k1].Position;
            areaWeightedNormal = glm::cross(edgeAB, edgeAC);
            vertices[k1].Normal += areaWeightedNormal;
            vertices[k2].Normal += areaWeightedNormal;
            vertices[k3].Normal += areaWeightedNormal;

            k1 = k3;
            k3 = (u+1) * vStep + v + 1;

            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);
            edgeAB = vertices[k2].Position - vertices[k1].Position;
            edgeAC = vertices[k3].Position - vertices[k1].Position;
            areaWeightedNormal = glm::cross(edgeAB, edgeAC);
            vertices[k1].Normal += areaWeightedNormal;
            vertices[k2].Normal += areaWeightedNormal;
            vertices[k3].Normal += areaWeightedNormal;
        }

    }

    for(auto & vertice : vertices)
        glm::normalize(vertice.Normal);

    this->addMesh(std::make_shared<Mesh>(vertices, indices));
    vertices.clear();
    indices.clear();
}



