//
// Created by Robin on 26/02/2020.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include <glm/vec3.hpp>
#include <GL/gl.h>
#include "shader.h"
#include "model.h"

class Light {
    /**
     * Base class for lights
     */
public:
    /**
     * Constructor
     * @param ambient
     * @param diffuse
     * @param specular
     * @param representation
     */
    Light(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,const std::shared_ptr<Model> &representation);
    /**
     * Destructor
     */
    virtual ~Light();

    Light(const Light &) = delete;

    Light(Light &&) = delete;

    Light &operator=(const Light &) = delete;

    Light &&operator=(Light &&) = delete;
    /**
     * Ambient getter
     * @return
     */
    const glm::vec3 & ambient() const { return _ambient; }
    /**
     * Ambient setter
     * @return
     */
    glm::vec3 & ambient() { return _ambient; }
    /**
     * Diffuse getter
     * @return
     */
    const glm::vec3 & diffuse() const { return _diffuse; }
    /**
     * Diffuse setter
     * @return
     */
    glm::vec3 & diffuse() { return _diffuse; }
    /**
     * Specular getter
     * @return
     */
    const glm::vec3 & specular() const { return _specular; }
    /**
     * Specular setter
     * @return
     */
    glm::vec3 & specular() { return _specular; }

    /**
     * Draw light model
     * @param shader
     */
    void drawLight(Shader &shader);
    /**
     * Add light to Shader
     * @param shader
     */
    virtual void addToShader(Shader &shader);

private:
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

protected:

    std::shared_ptr<Model> _representation; //Model of light
};


class PointLight : public Light {

public:
    /**
     * Constructor
     * Initialize light from default values
     */
    PointLight();
    /**
     * Constructor
     * Initialize light from default values
     * @param position
     */
    PointLight(glm::vec3 pos);
    /**
     * Destructor
     */
    ~PointLight();
    /**
     * Add pointLight to Shader
     * @param shader
     */
    void addToShader(Shader &shader) override;
    /**
     * Constant getter
     * @return
     */
    GLfloat getConst()const {return _constant;}
    /**
     * Linear getter
     * @return
     */
    GLfloat getLin() const{return _linear;}
    /**
     * Quadratic getter
     * @return
     */
    GLfloat getQuad() const{return _quadratic;}
    /**
     * Quadratic setter
     * @param val
     */
    void setQuadratic(double val){ _quadratic = val;}
    /**
     * Linear setter
     * @param val
     */
    void setLinear(double val){ _linear = val;}
    /**
     * Constant setter
     * @param val
     */
    void setConstant(double val){ _constant = val;}


protected:
    GLfloat _constant;
    GLfloat _linear;
    GLfloat _quadratic;
};


class SpotLight : public PointLight{
public:
    /**
     * Constructor
     */
    SpotLight();
    /**
     * Constructor
     * @param pos
     */
    explicit SpotLight(glm::vec3 pos);
    /**
     * Destructor
     */
    ~SpotLight() override;
    /**
     * Add spotLight to Shader
     * @param shader
     */
    void addToShader(Shader &shader) override;
private:
    glm::vec3 _direction;
    float _innerCutoff;
    float _outerCutoff;
    float _intensity;
};


#endif //ENGINE_LIGHT_H
