//
// Created by Robin on 26/02/2020.
//

#include <src/models/cube.h>
#include "light.h"

Light::Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const std::shared_ptr<Model> &representation):
    _ambient{ambient},
    _diffuse{diffuse},
    _specular{specular},
    _representation(representation)
{

}

Light::~Light()
{

}

void Light::addToShader(Shader &shader)
{

}

void Light::drawLight(Shader &shader)
{
    _representation->drawModel(shader);
}


PointLight::~PointLight(){}

PointLight::PointLight():
    Light(glm::vec3(0.5f),glm::vec3(2.f),glm::vec3(1.f),std::make_shared<Cube>()),
    _constant{1.f},
    _linear{0.99f},
    _quadratic{0.032f}

{
    _representation->setPosition(glm::vec3(0.7f,0.2f,2.0f));
}


void PointLight::addToShader(Shader &shader)
{
    shader.use();
 shader.addPointLight(_constant,_linear,_quadratic,_representation->getPosition(),ambient(),diffuse(),specular());
}

PointLight::PointLight(glm::vec3 pos):
PointLight()
{
    _representation->setScale(glm::vec3(0.1f));
    _representation->setPosition(pos);
}

SpotLight::SpotLight():
        PointLight(),
        _direction(glm::vec3(0.0f,0.f,-1.0f)),
        _innerCutoff(glm::cos(glm::radians(12.f))),
        _outerCutoff(glm::cos(glm::radians(16.f))),
        _intensity(1.0f)
{

}

SpotLight::~SpotLight()
{

}

void SpotLight::addToShader(Shader &shader)
{
    shader.addSpotLight(_direction,_innerCutoff,_outerCutoff,_constant, _linear, _quadratic,_intensity ,_representation->getPosition(),ambient(),diffuse(),specular());
}

SpotLight::SpotLight(glm::vec3 pos):
        SpotLight()
{
    _representation->setScale(glm::vec3(0.1f));
    _representation->setPosition(pos);
}
