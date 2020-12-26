//
// Created by robin on 25/12/2020.
//

#ifndef ENGINE_CYLINDER_H
#define ENGINE_CYLINDER_H

#include "core/asset.h"
class Cylinder : public Asset{
public:
    Cylinder(){
        glm::vec3 base=glm::vec3(0,0,0);
        glm::vec3 axis = glm::vec3(1,0,0);
        float radius = .5f;
        float length = 3.;
        int subdiv1 = 64;
        int subdiv2 = 512;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        glm::vec3 x = glm::vec3(0,1,0); //orthogonal(axis);
        glm::vec3 y = cross(axis, x);

        for(int i=0; i<subdiv2; i++)
        {
            float offset = float(i)/float(subdiv2-1);
            float offset2 = (offset-0.5)*length;
            for(int j=0; j<subdiv1; j++)
            {
                float angle = 2.*glm::pi<float>()*float(j)/float(subdiv1);
                Vertex nv;
                nv.position = base+offset2*axis+radius*glm::cos(angle)*x+radius*glm::sin(angle)*y;
                nv.normal = normalize(glm::cos(angle)*x+glm::sin(angle)*y);
                vertices.push_back(nv);
            }
        }


        for(unsigned int i=0; i<subdiv2-1; i++)
        {
            for(unsigned int j=0; j<subdiv1; j++)
            {
                GLuint f1 {i*subdiv1+j};
                GLuint f2 {i*subdiv1+(j+1)%subdiv1};
                GLuint f3 {i*subdiv1+j+subdiv1};
                indices.push_back(f1);
                indices.push_back(f2);
                indices.push_back(f3);
                f1 = i*subdiv1+(j+1)%subdiv1;
                f2 = i*subdiv1+j+subdiv1;
                f3 = i*subdiv1+(j+1)%subdiv1+subdiv1;

                indices.push_back(f1);
                indices.push_back(f2);
                indices.push_back(f3);
            }

        }
        addMesh(std::make_shared<Mesh>(vertices,indices,std::make_shared<Material>()));
    }

};


#endif //ENGINE_CYLINDER_H
