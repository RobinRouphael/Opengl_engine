//
// Created by Robin on 24/02/2020.
//

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H
#include <stb/stb_image.h>
#include "core/shader.h"
class Texture{


/**
 * Base class for textures
 */
public:
    enum class TextureType{DIFFUSE, SPECULAR, SHADOW};
    /**
     * Constructor
     * @param tr_location of image file
     */
    Texture(const std::string &tr_location, TextureType t_type);

    Texture(GLuint t_existingTex, TextureType t_type);
    Texture(const Texture &tr_tex):
    m_type{tr_tex.m_type},
    m_height{tr_tex.m_height},
    m_id{tr_tex.m_id},
    m_width{tr_tex.m_width},
    m_nrChannels{tr_tex.m_nrChannels}
    {

    }

    Texture(Texture &&trr_tex) noexcept
            : m_type{trr_tex.m_type},
              m_height{trr_tex.m_height},
              m_id{trr_tex.m_id},
              m_width{trr_tex.m_width},
              m_nrChannels{trr_tex.m_nrChannels}
    {

    }
    Texture &operator=(const Texture &trr_tex) noexcept {
        m_type =trr_tex.m_type;
        m_height=trr_tex.m_height;
        m_id =trr_tex.m_id;
        m_width=trr_tex.m_width;
        m_nrChannels=trr_tex.m_nrChannels;
        return *this;
    }
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
    [[nodiscard]] const std::string &getLocation() const;
    [[nodiscard]] const std::string getName() const;

private:
    //image file location
    GLuint m_id;
public:
    GLuint getMId() const;

private:
    int m_height;
    int m_width;
    int m_nrChannels;
    TextureType m_type;


};






#endif //ENGINE_TEXTURE_H
