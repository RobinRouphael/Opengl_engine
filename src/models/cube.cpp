//
// Created by Robin on 15/03/2020.
//

#include "cube.h"

Cube::Cube() :
        Asset(),
        m_resolution{3}
    {
        setAssetType(AssetType::Custom);
        setup();
    }

Cube::~Cube() {}

void Cube::setup()
{

    std::vector<glm::vec3> directions{
         {0.f, 0.f, 1.f}  // front
        ,{0.f, 0.f, -1.f} // back
        ,{0.f, 1.f, 0.f}  // top
        ,{0.f, -1.f, 0.f} // bottom
        ,{1.f, 0.f, 0.f}  // right
        ,{-1.f, 0.f, 0.f}  // left
    };
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    glm::vec3 yAxis;
    glm::vec3 xAxis;


    for (auto i =0; i< 6; i++){

        yAxis = glm::vec3(directions[i].y, directions[i].z, directions[i].x);
        xAxis = glm::cross(directions[i],yAxis);
        for(auto x = 0; x < m_resolution; x++){

            for (auto y = 0; y < m_resolution; y++){

                auto index = x+ y * m_resolution;
                auto yPourcent = y/(float(m_resolution - 1));
                auto xPourcent = x/(float(m_resolution - 1));


                Vertex v;
                v.position = directions[i] + (xPourcent - 0.5f) * xAxis * 2.f + (yPourcent - 0.5f) * yAxis * 2.f;
                v.normal = directions[i];
                vertices.push_back(v);

                if (x != m_resolution - 1 && y != m_resolution - 1 ) {
                    indices.push_back(index);
                    indices.push_back(index + m_resolution);
                    indices.push_back(index + m_resolution + 1);
                    indices.push_back(index + m_resolution + 1);
                    indices.push_back(index + 1);
                    indices.push_back(index);
                }

            }
        }
        addMesh(std::make_shared<Mesh>(vertices, indices,std::make_shared<Material>()));
        vertices.clear();
        indices.clear();

    }
}
