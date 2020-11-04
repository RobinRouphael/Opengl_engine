//
// Created by Robin on 24/02/2020.
//

#include "texture.h"




void Texture::bindToGL(const Shader &tr_shader, int t_num)
{
    glActiveTexture(GL_TEXTURE0 + t_num);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

Texture::Texture(GLuint t_existingTex, TextureType t_type):
        m_id(t_existingTex),
        m_type(t_type)
{

}

Texture::Texture(const std::string &tr_location, TextureType t_type):
        m_location(tr_location),
        m_type(t_type)
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(tr_location.c_str(), &m_width, &m_height, &m_nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (m_nrChannels == 1)
            format = GL_RED;
        else if (m_nrChannels == 3)
            format = GL_RGB;
        else if (m_nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

const std::string &Texture::getLocation() const {
    return m_location;
}

const std::string Texture::getName() const {
    switch(m_type){
        case TextureType::DIFFUSE:
            return std::string{"diffuseMap"};
        case TextureType::SPECULAR:
            return std::string{"specularMap"};
        default:
            return std::string{"shadowMap"};
    }
}

GLuint Texture::getMId() const {
    return m_id;
}






