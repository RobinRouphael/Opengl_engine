//
// Created by Robin on 10/03/2020.
//

#ifndef ENGINE_MATERIAL_H
#define ENGINE_MATERIAL_H



#include <opengl_stuff.h>

class Material {
public:
    Material() :
    _albedo {0.5f, 0.0f, 0.0f}
    , _metalness {0.8f}
    , _roughness {0.2f}
    , _ao {0.5f} {}

    Material(const glm::vec3 &albedo, float metalness, float roughness, float ao):
            _albedo {albedo}
            ,_metalness {metalness}
            ,_roughness {roughness}
            ,_ao {ao} {}


    const glm::vec3 &albedo() const {
        return _albedo;
    }

    float metalness() const {
        return _metalness;
    }
    float roughness() const {
        return _roughness;
    }
    float ambientOcclusion() const {
        return _ao;
    }

private:
    glm::vec3 _albedo;
    float _metalness;
    float _roughness;
    float _ao;
};


#endif //ENGINE_MATERIAL_H
