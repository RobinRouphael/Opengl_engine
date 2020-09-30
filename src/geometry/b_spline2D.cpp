//
// Created by robin on 29/09/2020.
//

#include "b_spline2D.h"

BSpline2D::BSpline2D() {
 _deg = 3;
 _nodalVectorV = std::vector<float>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
 _nodalVectorU = std::vector<float>{1,2,3,4,5,6,7,8,9,10,11,12};

    for(int i = 0; i < 10; i++) {
     auto uSpline = std::make_shared<BSpline>(_deg, std::vector<glm::vec3>{
             glm::vec3(0+i, 0, i), glm::vec3(1+i, 1, i),
             glm::vec3(2+i, 1, i),
             glm::vec3(3+i, 0, i), glm::vec3(4+i, -1, i), glm::vec3(5+i, 0, i), glm::vec3(6+i, 0, i), glm::vec3(7, 0, i)
     }, _nodalVectorU);

     _uSplines.emplace_back(std::move(uSpline));
    }

 std::vector<Vertex> vertices;
 std::vector<GLuint> indices;
 for(float v = _nodalVectorV[_deg]; v < _nodalVectorV[_nodalVectorV.size()-_deg-1]; v +=0.1){
     for(float u = _nodalVectorU[_deg]; u < _nodalVectorU[_nodalVectorU.size()-_deg-1]; u +=0.1) {
         Vertex vertex;
         vertex.Position = this->evaluate(u,v);
         vertices.push_back(vertex);

     }
 }
    int uStep = (_nodalVectorU[_nodalVectorU.size()-_deg-1] - _nodalVectorU[_deg])/0.1;
    int k1, k2, k3;
    for(int v = 0; v < uStep-1; v ++){
        for(int u = 0; u < uStep-1; u++){

                k1 = v * uStep + u;
                k2 = v * uStep + 1 + u;
                k3 = (v+1) * uStep + u;
            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);

                k1 = (v+1) * uStep+ u;
                k3 = (v+1) * uStep + u + 1;

            indices.emplace_back(k1);
            indices.emplace_back(k2);
            indices.emplace_back(k3);
        }

    }

 this->addMesh(std::make_shared<Mesh>(vertices, indices));
 vertices.clear();
 indices.clear();

}

BSpline2D::~BSpline2D() {

}

void BSpline2D::drawModel(Shader shader) {
    if(waitingToUpdate){
        waitingToUpdate=false;
        updateModel();
    }

    shader.use();
    shader.setMat4("model", getModel());
    shader.addMaterial(_material);
    _meshs[0]->drawMesh(shader);
}

glm::vec3 BSpline2D::evaluate(float u, float v) {
    std::vector<glm::vec3> uControlPoints;
    for(auto &uspline : _uSplines)
        uControlPoints.emplace_back(uspline->evaluate(u));

    auto k =  _deg+1;
    auto i = k;
    int dec = 0;
    while(v > _nodalVectorV[i])
    {
        i++;
        dec++;
    }
    auto tempPoints = std::vector<glm::vec3>(uControlPoints.begin()+dec, uControlPoints.begin()+dec+k);
    for( auto l = 0; l < _deg; ++l )
    {
        for( auto j = 0; j < k - 1; j++)
        {

            tempPoints[j] = ( ( _nodalVectorV[dec+k+j] - v ) / (_nodalVectorV[dec+k+j] - _nodalVectorV[dec+1+j]) ) * tempPoints[j] +
                            ( ( v - _nodalVectorV[dec+1+j] ) / (_nodalVectorV[dec+k+j] - _nodalVectorV[dec+1+j]) )* tempPoints[j+1];

        }
        dec++;
        k--;
    }


    return tempPoints[0];
}

