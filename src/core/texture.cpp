//
// Created by Robin on 24/02/2020.
//

#include "texture.h"




void Texture::bindToGL(const Shader &shader, int num)
{
    glActiveTexture(GL_TEXTURE0+ num);
    glBindTexture(GL_TEXTURE_2D, getID());
}

Texture::Texture(GLuint existingTex):
_id(existingTex)
{

}

Texture::Texture(const std::string &location):
    _location(location)
{
    GLuint id;
    int width, height, nrChannels;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(location.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    setHeight(height);
    setID(id);
    setWidth(width);
    setNRChannels(nrChannels);

}


Texture::~Texture()
{

}

void Texture::setID(GLuint id)
{
    _id=id;
}

void Texture::setHeight(int height)
{
    _height = height;
}

void Texture::setWidth(int width)
{
    _width = width;
}

void Texture::setNRChannels(int nrChannels)
{
    _nrChannels = nrChannels;
}

GLuint Texture::getID()
{
    return _id;
}

const std::string &Texture::getLocation()
{
    return _location;
}


