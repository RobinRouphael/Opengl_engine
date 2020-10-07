//
// Created by Robin on 22/02/2020.
//

#include "model.h"

Model::Model():
    _scale(1),
    _translation(0),
    _rotation(0),
    waitingToUpdate{false}
    {}

Model::~Model()
{

}

void Model::drawModel(Shader shader, GLuint glmode)
{

    if(waitingToUpdate){
        waitingToUpdate=false;
        updateModel();
    }
    shader.use();
    shader.setMat4("model", getModel());
    shader.addMaterial(_material);
    for(auto &m : _meshs)
        m->drawMesh(shader, glmode);
}

void Model::addMesh(std::shared_ptr<Mesh> mesh)
{
    _meshs.emplace_back(mesh);
}



void Model::updateModel() {}













