//
// Created by robin on 29/09/2020.
//

#include "b_spline2D.h"

#include <utility>

BSpline2D::BSpline2D(int deg, float step, std::vector<float> nodalVectorV, std::vector<float> nodalVectorU,
                     const std::vector<std::vector<glm::vec3>>& uSplinesPoints):
                     Model(),
                     _deg(deg),
                     _step(step),
                     _nodalVectorV(std::move(nodalVectorV)),
                     _nodalVectorU(std::move(nodalVectorU))
                     {
    for(auto &spline : uSplinesPoints)
        _uSplines.emplace_back(std::make_shared<BSpline>(_deg,spline,_nodalVectorU));

    createBSpline2D();

}

BSpline2D::~BSpline2D() = default;

void BSpline2D::createBSpline2D() {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    for(int u = _nodalVectorU[_deg]/_step; u < _nodalVectorU[_nodalVectorU.size()-_deg-1]/_step; u +=1 ){

        std::vector<glm::vec3> uControlPoints;
        for(auto &uspline : _uSplines)
            uControlPoints.emplace_back(uspline->evaluate(u*_step));
        _vSpline = std::make_shared<BSpline>(_deg, uControlPoints, _nodalVectorV);
        for(int v = _nodalVectorV[_deg]/_step; v< _nodalVectorV[_nodalVectorV.size()-_deg-1]/_step; v +=1 ) {
            Vertex vertex;
            vertex.Position = _vSpline->evaluate(v*_step);
            vertices.push_back(vertex);

        }
        uControlPoints.clear();
    }
    int vStep = (_nodalVectorV[_nodalVectorV.size()-_deg-1] - _nodalVectorV[_deg])/_step ;
    int uStep = (_nodalVectorU[_nodalVectorU.size()-_deg-1] - _nodalVectorU[_deg])/_step ;
    int k1, k2, k3;
    for(int u = 0; u < uStep-1; u ++){
        for(int v = 0; v < vStep-1; v++){

            k1 = u * vStep + v;
            k2 = u * vStep + 1 + v;
            k3 = (u+1) * vStep + v;
            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);

            k1 = k3;
            k3 = (u+1) * vStep + v + 1;

            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);
        }

    }

    this->addMesh(std::make_shared<Mesh>(vertices, indices));
    vertices.clear();
    indices.clear();
}


