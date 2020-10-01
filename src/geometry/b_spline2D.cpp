//
// Created by robin on 29/09/2020.
//

#include "b_spline2D.h"

BSpline2D::BSpline2D() {
    _step = 0.1;
 _deg = 2;
 _nodalVectorV = std::vector<float>{1,2,3,4,5,6,7};
 _nodalVectorU = std::vector<float>{1,2,3,4,5,6,7};
 auto uSpline1 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
         glm::vec3(-2.63, 0,-2.01),
         glm::vec3(-2.62, 0,0.17),
         glm::vec3(-2.51, 0,1.98),
         glm::vec3(-2.48, 0,3.74)
 },_nodalVectorU);
    auto uSpline2 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(-1.18, 0,-1.92),
            glm::vec3(-1.09, 1.41,-0.28),
            glm::vec3(-1, 1.4,2),
            glm::vec3(-1, 0,3.48)
    },_nodalVectorU);
    auto uSpline3 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(-1.18, 0,-1.92),
            glm::vec3(-1.09, 1.41,-0.28),
            glm::vec3(-1, 1.4,2),
            glm::vec3(-1, 0,3.48)
    },_nodalVectorU);
    auto uSpline4 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(-1.18, 0,-1.92),
            glm::vec3(-1.09, 1.41,-0.28),
            glm::vec3(-1, 1.4,2),
            glm::vec3(-1, 0,3.48)
    },_nodalVectorU);
    /*auto uSpline1 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(0, 0,0),
            glm::vec3(1, 0,0),
            glm::vec3(2, 0,0),
            glm::vec3(3, 0,0),
    },_nodalVectorU);
    auto uSpline2 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(0, 0,1),
            glm::vec3(1, 0,1),
            glm::vec3(2, 0,1),
            glm::vec3(3, 0,1),
    },_nodalVectorU);
    auto uSpline3 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(0, 0,2),
            glm::vec3(1, 0,2),
            glm::vec3(2, 0,2),
            glm::vec3(3, 0,2),
    },_nodalVectorU);
    auto uSpline4 = std::make_shared<BSpline>(_deg,std::vector<glm::vec3>{
            glm::vec3(0, 0,3),
            glm::vec3(1, 0,3),
            glm::vec3(2, 0,3),
            glm::vec3(3, 0,3),
    },_nodalVectorU);*/
    _uSplines.emplace_back(std::move(uSpline1));
    _uSplines.emplace_back(std::move(uSpline2));
    _uSplines.emplace_back(std::move(uSpline3));
    _uSplines.emplace_back(std::move(uSpline4));
    /*for(int i = 0; i < 8; i++) {
     auto uSpline = std::make_shared<BSpline>(_deg, std::vector<glm::vec3>{
             glm::vec3(0+i, 0, i), glm::vec3(1+i, 1, i),
             glm::vec3(2+i, 1, i),
             glm::vec3(3+i, 0, i), glm::vec3(4+i, 2, i), glm::vec3(5+i, 0, i), glm::vec3(6+i, 0, i), glm::vec3(7+i, 0, i)
     }, _nodalVectorU);

     _uSplines.emplace_back(std::move(uSpline));
    }*/

 std::vector<Vertex> vertices;
 std::vector<GLuint> indices;
 GLuint indice = 0;
 for(int u = _nodalVectorU[_deg]/_step; u < _nodalVectorU[_nodalVectorU.size()-_deg-1]/_step; u +=1 ){

     std::vector<glm::vec3> uControlPoints;
     for(auto &uspline : _uSplines)
         uControlPoints.emplace_back(uspline->evaluate(u*_step));
     for(int v = _nodalVectorV[_deg]/_step; v< _nodalVectorV[_nodalVectorV.size()-_deg-1]/_step; v +=1 ) {
         Vertex vertex;
         vertex.Position = this->evaluate(uControlPoints,v*_step);
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
    /*for(auto x : _uSplines){
        x->compute(_step);
        x->drawModel(shader);
    }*/
}

glm::vec3 BSpline2D::evaluate(const std::vector<glm::vec3> &uControlPoints, float v) {
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

