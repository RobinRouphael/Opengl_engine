//
// Created by Robin on 01/03/2020.
//

#include "icosphere.h"

Icosphere::Icosphere() :
    Model(),
    _nbsubdivisions(2)
{
    createIcosahedron();
    for(int i =0; i< _nbsubdivisions; i++)
        createSubdivisions();
}

void Icosphere::createIcosahedron()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    const float H_ANGLE = M_PI / 180 * 72;    // 72 degree = 360 / 5
    const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree
    float z, xy;                            // coords
    float hAngle1 = -M_PI / 2 - H_ANGLE / 2;  // start from -126 deg at 1st row
    float hAngle2 = -M_PI / 2;                // start from -90 deg at 2nd row

// the first top vertex at (0, 0, r)
    Vertex vertex;
    vertex.Position = vertex.Normal = glm::vec3(0.f, 1.f, 0.f);
    vertices.push_back(vertex);

// compute 10 vertices at 1st and 2nd rows
    for(auto i = 1; i <= 5; ++i)
    {
        z  = sinf(V_ANGLE);            // elevaton
        xy = cosf(V_ANGLE);            // length on XY plane

        vertex.Position = vertex.Normal = glm::vec3(xy * glm::cos(hAngle1), z, xy * glm::sin(hAngle1));
        vertices.push_back(vertex);

        vertex.Position = vertex.Normal = glm::vec3(xy * glm::cos(hAngle2), -z, xy * glm::sin(hAngle2));
        vertices.push_back(vertex);

        // next horizontal angles
        hAngle1 += H_ANGLE;
        hAngle2 += H_ANGLE;
    }
    //Bottom vertex
    vertex.Position = vertex.Normal = glm::vec3(0.f, -1.f, 0.f);
    vertices.push_back(vertex);

    for (auto i = 1;i <= 9;i+=2) {

        // Top
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(mod_eq(i+2,10));
        // Middle
        indices.push_back(mod_eq(i+2,10));
        indices.push_back(i);
        indices.push_back(mod_eq(i+1,10));

        indices.push_back(mod_eq(i+2,10));
        indices.push_back(mod_eq(i+1,10));
        indices.push_back(mod_eq(i+3,10));
        // Bottom
        indices.push_back(mod_eq(i+3,10));
        indices.push_back(mod_eq(i+1,10));
        indices.push_back(11);
    }
    _meshs.clear();
    addMesh(std::make_shared<Mesh>(vertices,indices));
    _vertices = vertices;
    _indices = indices;
}

void Icosphere::createSubdivisions()
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint i1, i2, i3;
    Vertex v1, v2, v3;
    int index = 0;

    for (auto i = 0 ; i < _indices.size() ; i += 3) {
        i1 = _indices[i];
        i2 = _indices[i+1];
        i3 = _indices[i+2];

        v1.Position = v1.Normal = glm::normalize(_vertices[i1].Position + _vertices[i2].Position);
        v2.Position = v2.Normal = glm::normalize(_vertices[i2].Position + _vertices[i3].Position);
        v3.Position = v3.Normal = glm::normalize(_vertices[i1].Position + _vertices[i3].Position);

        // top triangle
        vertices.push_back(_vertices[i1]);
        vertices.push_back(v1);
        vertices.push_back(v3);
        // bottom left triangle
        vertices.push_back(v1);
        vertices.push_back(_vertices[i2]);
        vertices.push_back(v2);
        // bottom right triangle
        vertices.push_back(v3);
        vertices.push_back(v2);
        vertices.push_back(_vertices[i3]);
        // bottom middle triangle
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);

        for (int j = 0 ; j < 12 ; j++)
            indices.push_back(GLuint(index + j));
        index += 12;
    }

    _meshs[0] = std::make_shared<Mesh>(vertices,indices);
    _vertices = vertices;
    _indices = indices;
}

Icosphere::~Icosphere() {

}

void Icosphere::setNBSubdivisions(int val)
{
    _nbsubdivisions =val;
    waitingToUpdate = true;
}


int Icosphere::getNBSubdivisions()
{
    return _nbsubdivisions;
}



void Icosphere::updateModel()
{
    createIcosahedron();
    for(int i =0; i< _nbsubdivisions; i++)
        createSubdivisions();
}


