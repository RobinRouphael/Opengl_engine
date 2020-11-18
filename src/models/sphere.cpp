//
// Created by Robin on 22/02/2020.
//

#include "sphere.h"
#include "marchingCube.h"


Sphere::Sphere():
    Sphere(20,20)
    {}

Sphere::Sphere(int t_nbStacks, int t_nbSectors):
        Asset(),
        m_nb_sectors(t_nbSectors),
        m_nb_stacks(t_nbStacks)
        {
    //MarchingCube mc{};
    //addMesh(mc.generateMesh([&](glm::vec3 point){ return pow(point.x,2) + pow(point.y,2) + pow(point.z,2); }));
    addMesh(std::make_shared<Mesh>(createVertices(),createIndices(),std::make_shared<Material>()));
    setAssetType(AssetType::Sphere);
    }

Sphere::~Sphere(){}


std::vector<Vertex> Sphere::createVertices()
{
    std::vector<Vertex> vertices;
    float delta = 0;
    float phi =0;
    float x,y,z,xy;
    float lengthInv = 1.0f;
    for(int i = 0; i <= m_nb_stacks; i++){

        delta = M_PI * i / m_nb_stacks;
        z = cosf(delta);
        xy = sinf(delta);

        for(int j = 0; j <= m_nb_sectors; j++){

            phi = 2 * M_PI * j / m_nb_sectors;
            x = xy * cosf(phi);
            y = xy * sinf(phi);
            Vertex v;
            v.position = glm::vec3(x, y, z);
            v.normal = glm::vec3(x * lengthInv, y * lengthInv, z * lengthInv);
            v.texCoords = glm::vec2(float(i) / m_nb_stacks, float(j) / m_nb_sectors);
            vertices.emplace_back(v);

        }
    }
    return vertices;
}

std::vector<GLuint> Sphere::createIndices()
{
    std::vector<GLuint> indices;
    int k1, k2;
    for(int i = 0; i < m_nb_stacks; i++)
    {
        k1 = i * (m_nb_sectors + 1);     // beginning of current stack
        k2 = k1 + m_nb_sectors + 1;      // beginning of next stack

        for(int j = 0; j < m_nb_sectors; ++j, ++k1, ++k2)
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
            if(i != (m_nb_stacks - 1))
            {
                indices.emplace_back(k1 + 1);
                indices.emplace_back(k2);
                indices.emplace_back(k2 + 1);
            }
        }
    }
    return indices;
}

void Sphere::setNbStacks(int t_nbStacks)
{
    m_nb_stacks = t_nbStacks;
    setWaitingToUpdate(true);
}

void Sphere::setNbSectors(int t_nbSectors){
    m_nb_sectors = t_nbSectors;
    setWaitingToUpdate(true);
}


int Sphere::getNBStacks()
{
    return m_nb_stacks;
}

void Sphere::updateModel()
{
    setMeshs(std::vector<std::shared_ptr<Mesh>>{std::make_shared<Mesh>(createVertices(), createIndices(), std::make_shared<Material>())});
}


int Sphere::getNBSectors()
{
    return m_nb_sectors;
}









