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
     * @param tr_location of image file
     */
    Texture(const std::string &tr_location);

    Texture(GLuint t_existingTex);
    /**
     * Destructor
     */
    ~Texture();
    /**
     * Bind texture to OpenGL context
     * @param tr_shader
     * @param t_num
     */
    void bindToGL(const Shader &tr_shader, int t_num);



private:
    std::string m_location;
public:
    const std::string &getLocation() const;

private:
    //image file location
    GLuint m_id;
    int m_height;
    int m_width;
    int m_nrChannels;
};






#endif //ENGINE_TEXTURE_H
