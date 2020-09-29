//
// Created by robin on 29/09/2020.
//

#include "b_spline2D.h"

BSpline2D::BSpline2D() {
 _deg = 3;
 _nodalVector = std::vector<float>{1,2,3,4,5,6,7,8,9,10,11,12};
 for(int i = 0; i < 10; i++) {
     auto uSpline = std::make_shared<BSpline>(_deg, std::vector<glm::vec3>{
             glm::vec3(0+i, 0, i), glm::vec3(1+i, 1, i),
             glm::vec3(2+i, 1, i),
             glm::vec3(3+i, 0, i), glm::vec3(4+i, -5, i), glm::vec3(5+i, 0, i), glm::vec3(6+i, 0, i), glm::vec3(7, 0, i)
     }, _nodalVector);

     _uSplines.emplace_back(std::move(uSpline));
 }

 std::vector<Vertex> vertices;
 std::vector<GLuint> indices;
 GLuint indice = 0;
 for(float v = _nodalVector[_deg]; v < _nodalVector[8]; v +=0.1){
     for(float u = _nodalVector[_deg]; u < _nodalVector[8]; u +=0.1) {
         Vertex vertex;
         vertex.Position = this->evaluate(u,v);
         vertices.push_back(vertex);
         indices.push_back(indice);
         indice++;

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
    /*for(auto & uspline : _uSplines) {
        uspline->compute(0.1);
        uspline->drawModel(shader);
    }*/
    _meshs[0]->drawLineMesh(shader);
}

glm::vec3 BSpline2D::evaluate(float u, float v) {
    std::vector<glm::vec3> uControlPoints;
    for(auto &uspline : _uSplines)
        uControlPoints.emplace_back(uspline->evaluate(u));

    auto k =  _deg+1;
    auto i = k;
    int dec = 0;
    while(v > _nodalVector[i])
    {
        i++;
        dec++;
    }
    auto tempPoints = std::vector<glm::vec3>(uControlPoints.begin()+dec, uControlPoints.begin()+dec+k);
    for( auto l = 0; l < _deg; ++l )
    {
        for( auto j = 0; j < k - 1; j++)
        {

            tempPoints[j] = ( ( _nodalVector[dec+k+j] - v ) / (_nodalVector[dec+k+j] - _nodalVector[dec+1+j]) ) * tempPoints[j] +
                            ( ( v - _nodalVector[dec+1+j] ) / (_nodalVector[dec+k+j] - _nodalVector[dec+1+j]) )* tempPoints[j+1];

        }
        dec++;
        k--;
    }


    return tempPoints[0];
}

