//
// Created by Robin on 15/03/2020.
//

#include "cube.h"

Cube::Cube() :
    Model(),
    _resolution{3}
    {
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
        for(auto x = 0; x < _resolution; x++){

            for (auto y = 0; y< _resolution; y++){

                auto index = x+y*_resolution;
                auto yPourcent = y/(float(_resolution-1));
                auto xPourcent = x/(float(_resolution-1));


                Vertex v;
                v.Position = directions[i] + (xPourcent-0.5f)*xAxis*2.f + (yPourcent-0.5f)*yAxis*2.f;
                v.Normal = directions[i];
                vertices.push_back(v);

                if ( x != _resolution - 1 && y != _resolution - 1 ) {
                    indices.push_back(index);
                    indices.push_back(index + _resolution);
                    indices.push_back(index + _resolution + 1);
                    indices.push_back(index + _resolution + 1);
                    indices.push_back(index + 1);
                    indices.push_back(index);
                }

            }
        }
        addMesh(std::make_shared<Mesh>(vertices, indices));
        vertices.clear();
        indices.clear();

    }
}
