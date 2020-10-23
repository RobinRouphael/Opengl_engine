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

    Texture(GLuint existingTex);
    /**
     * Destructor
     */
    ~Texture();
    /**
     * Bind texture to OpenGL context
     * @param shader
     * @param num
     */
    void bindToGL(const Shader &shader, int num);
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






#endif //ENGINE_TEXTURE_H
