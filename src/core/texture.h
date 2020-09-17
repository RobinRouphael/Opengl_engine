//
// Created by Robin on 24/02/2020.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include <stb/stb_image.h>
#include "shader.h"
class Texture{
/**
 * Base class for textures
 */
public:
    /**
     * Constructor
     * @param location of image file
     */
    Texture(const std::string &location);
    /**
     * Destructor
     */
    ~Texture();
    /**
     * Bind texture to OpenGL context
     * @param shader
     * @param num
     */
    virtual void bindToGL(const Shader &shader, int num) = 0;
    /**
     * Set texture ID
     * @param id
     */
    void setID(GLuint id);
    /**
     * Set Height
     * @param height
     */
    void setHeight(int height);
    /**
     * Set Width
     * @param width
     */
    void setWidth(int width);
    /**
     * Set NR Channels
     * @param nrChannels
     */
    void setNRChannels(int nrChannels);
    /**
     * ID getter
     * @return
     */
    GLuint getID();
    /**
     * Location getter
     * @return
     */
    const std::string &getLocation();


private:
    std::string _location; //image file location
    GLuint _id;
    int _height;
    int _width;
    int _nrChannels;
};



class DiffuseMap : public Texture{
    /**
     * Diffuse texture
     */
public:
    /**
     * Constructor
     * @param location
     */
    explicit DiffuseMap(const std::string &location):
            Texture(location){}
    /**
     * Destructor
     */
    ~DiffuseMap(){}
    /**
     * Bind to OpenGL context
     * @param shader
     * @param num
     */
    void bindToGL(const Shader &shader, int num) override;

};

class SpecularMap : public Texture{
    /**
     * Specular Texture
     */
public:
    /**
     * Constructor
     * @param location
     */
    explicit SpecularMap(const std::string &location):
            Texture(location){}
    /**
     * Destructor
     */
    ~SpecularMap(){}
    /**
     * Bind to OpenGL context
     * @param shader
     * @param num
     */
    void bindToGL(const Shader &shader, int num) override;
};
class NormalMap : public Texture{
public:
    /**
     * Constructor
     * @param location
     */
    explicit NormalMap(const std::string &location):
            Texture(location){}
    /**
     * Destructor
     */
    ~NormalMap(){}
    /**
     * Bind to OpenGL context
     * @param shader
     * @param num
     */
    void bindToGL(const Shader &shader, int num) override;
};
class HeightMap : public Texture{
public:
    /**
     * Constructor
     * @param location
     */
    explicit HeightMap(const std::string &location):
            Texture(location){}
    /**
     * Destructor
     */
    ~HeightMap(){}
    /**
     * Bind to OpenGL context
     * @param shader
     * @param num
     */
    void bindToGL(const Shader &shader, int num) override;
};


#endif //ENGINE_TEXTURE_H
