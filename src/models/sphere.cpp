//
// Created by Robin on 22/02/2020.
//

#include "sphere.h"


Sphere::Sphere():
    Model(),
    _nbSectors(20),
    _nbStacks(20)
    {
        addMesh(std::make_shared<Mesh>(createVertices(),createIndices()));
    }

Sphere::~Sphere(){}


std::vector<Vertex> Sphere::createVertices()
{
    std::vector<Vertex> vertices;
    float delta = 0;
    float phi =0;
    float x,y,z,xy;
    float lengthInv = 1.0f;
    for(int i = 0; i<= _nbStacks; i++){

        delta = M_PI * i/_nbStacks;
        z = cosf(delta);
        xy = sinf(delta);

        for(int j = 0; j<= _nbSectors; j++){

            phi = 2*M_PI*j/_nbSectors;
            x = xy * cosf(phi);
            y = xy * sinf(phi);
            Vertex v;
            v.Position = glm::vec3(x,y,z);
            v.Normal = glm::vec3(x*lengthInv,y*lengthInv,z*lengthInv);
            v.TexCoords = glm::vec2( float(j)/_nbSectors,float(i)/_nbStacks);
            vertices.emplace_back(v);

        }
    }
    return vertices;
}

std::vector<GLuint> Sphere::createIndices()
{
    std::vector<GLuint> indices;
    int k1, k2;
    for(int i = 0; i < _nbStacks; i++)
    {
        k1 = i * (_nbSectors + 1);     // beginning of current stack
        k2 = k1 + _nbSectors + 1;      // beginning of next stack

        for(int j = 0; j < _nbSectors; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding first and last stacks
            // k1 => k2 => k1+1
            if(i != 0)
            {
                indices.emplace_back(k1);
                indices.emplace_back(k2);
                indices.emplace_back(k1 + 1);
            }

            // k1+1 => k2 => k2+1
            if(i != (_nbStacks-1))
            {
                indices.emplace_back(k1 + 1);
                indices.emplace_back(k2);
                indices.emplace_back(k2 + 1);
            }
        }
    }
    return indices;
}

void Sphere::setNbStacks(int nbStacks)
{
    _nbStacks = nbStacks;
    waitingToUpdate = true;
}

void Sphere::setNbSectors(int nbSectors){
    _nbSectors = nbSectors;
    waitingToUpdate = true;
}


int Sphere::getNBStacks()
{
    return _nbStacks;
}

void Sphere::updateModel()
{
    if(_textureDiffuse.get())
        _meshs[0] = std::make_shared<Mesh>(createVertices(),createIndices(),std::vector<std::shared_ptr<Texture>>{_textureDiffuse});
    else
        _meshs[0] = std::make_shared<Mesh>(createVertices(),createIndices());
}


int Sphere::getNBSectors()
{
    return _nbSectors;
}

void Sphere::setTextureDiffuse(const std::shared_ptr<Texture> &texture)
{
    _textureDiffuse =texture;
    waitingToUpdate = true;
}





