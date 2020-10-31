//
// Created by robin on 23/10/2020.
//

#include "frameBuffer.h"

GLuint FrameBuffer::s_default_fbo{0};

FrameBuffer::~FrameBuffer() {
    for (GLuint &b : m_buffers) {
        glDeleteBuffers(1, &b);
    }
    for (GLuint &t : m_textures) {
        glDeleteTextures(1, &t);
    }
    glDeleteFramebuffers(1, &m_fbo);
}


void FrameBuffer::use() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        glBindFramebuffer(GL_FRAMEBUFFER, s_default_fbo);
        return;
    }
    glViewport(0, 0, m_width, m_height);
}

void FrameBuffer::stop(int width, int height) const {
    glBindFramebuffer(GL_FRAMEBUFFER, s_default_fbo);
    glViewport(0, 0, width, height);
}

void FrameBuffer::drawBuffers() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    auto *buffers = new GLenum[m_num_color];
    for (int i = 0; i < m_num_color; ++i)
        buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    glDrawBuffers(m_num_color, buffers);
    delete[] buffers;
    glBindFramebuffer(GL_FRAMEBUFFER, s_default_fbo);
}


//Add Buffers
//---------------------------------------------------------------------------------------------------------------------------

void FrameBuffer::addBuffer(GLuint t_format, GLuint t_attachment) {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (m_num_samples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, t_format, m_width, m_height);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_num_samples, t_format, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, t_attachment, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, s_default_fbo);
    m_buffers.push_back(rbo);
}

void FrameBuffer::addColorBuffer() {
    if (m_num_color > GL_COLOR_ATTACHMENT31) return;
    addBuffer(GL_RGB, GL_COLOR_ATTACHMENT0 + m_num_color++ );
}

void FrameBuffer::addDepthBuffer() {
    if (m_is_depth) return;
    addBuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
    m_is_depth = true;
}

void FrameBuffer::addStencilBuffer() {
    if (m_is_stencil) return;
    addBuffer(GL_STENCIL_INDEX, GL_STENCIL_ATTACHMENT );
    m_is_stencil = true;
}

void FrameBuffer::addDepthStencilBuffer() {
    if (m_is_stencil_depth) return;
    addBuffer(GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT);
    m_is_stencil_depth = true;
}



//Add Textures
//---------------------------------------------------------------------------------------------------------------------------

void FrameBuffer::generateTexture(GLuint &t_texture, GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border) const {
    glGenTextures(1, &t_texture);
    glBindTexture(GL_TEXTURE_2D, t_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, t_internalFormat, m_width, m_height, 0, t_format, t_type, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if(t_border)
    {
        //Border color
        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
}

void FrameBuffer::addTexture(GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border, GLuint t_attachment) {
    //Bind
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    //Texture creation
    GLuint texture;
    generateTexture(texture, t_internalFormat, t_format, t_type, t_border);
    //Attach to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, t_attachment, GL_TEXTURE_2D, texture, 0);
    //Unbind
    glBindFramebuffer(GL_FRAMEBUFFER, s_default_fbo);
    m_textures.push_back(texture);
}

void FrameBuffer::addColorTexture() {
    if (m_num_color > GL_COLOR_ATTACHMENT31) return;
    addTexture(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE,false, GL_COLOR_ATTACHMENT0 + m_num_color++);
}

void FrameBuffer::addDepthTexture() {
    if (m_is_depth) return;
    addTexture(GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT, GL_FLOAT,true,GL_DEPTH_ATTACHMENT);
    m_is_depth = true;

}

void FrameBuffer::addStencilTexture() {
    if (m_is_stencil) return;
    addTexture(GL_STENCIL_INDEX, GL_STENCIL_INDEX,GL_INT,true,GL_STENCIL_ATTACHMENT);
    m_is_stencil = true;
}

void FrameBuffer::addDepthStencilTexture() {
    if (m_is_stencil_depth) return;
    addTexture(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,true,GL_DEPTH_STENCIL_ATTACHMENT);
    m_is_stencil_depth = true;
}








