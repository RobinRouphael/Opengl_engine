//
// Created by robin on 23/10/2020.
//

#include "frameBuffer.h"

GLuint FrameBuffer::default_fbo{0};

FrameBuffer::~FrameBuffer() {
    for (GLuint &b : buffers_) {
        glDeleteBuffers(1, &b);
    }
    for (GLuint &t : textures_) {
        glDeleteTextures(1, &t);
    }
    glDeleteFramebuffers(1, &fbo_);
}


void FrameBuffer::use() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
        return;
    }
    glViewport(0, 0, width_, height_);
}

void FrameBuffer::stop(int width, int height) const {
    glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
    glViewport(0, 0, width, height);
}

void FrameBuffer::drawBuffers() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    auto *buffers = new GLenum[num_color];
    for (int i = 0; i < num_color; ++i)
        buffers[i] = GL_COLOR_ATTACHMENT0 + i;
    glDrawBuffers(num_color, buffers);
    delete[] buffers;
    glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
}


//Add Buffers
//---------------------------------------------------------------------------------------------------------------------------

void FrameBuffer::addBuffer(GLuint format, GLuint attachment) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (num_samples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, format, width_, height_);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, num_samples, format, width_, height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
    buffers_.push_back(rbo);
}

void FrameBuffer::addColorBuffer() {
    if (num_color > GL_COLOR_ATTACHMENT31) return;
    addBuffer(GL_RGB, GL_COLOR_ATTACHMENT0 + num_color++ );
}

void FrameBuffer::addDepthBuffer() {
    if (depth_) return;
    addBuffer(GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT);
    depth_ = true;
}

void FrameBuffer::addStencilBuffer() {
    if (stencil_) return;
    addBuffer(GL_STENCIL_INDEX, GL_STENCIL_ATTACHMENT );
    stencil_ = true;
}

void FrameBuffer::addDepthStencilBuffer() {
    if (stencil_depth) return;
    addBuffer(GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT);
    stencil_depth = true;
}



//Add Textures
//---------------------------------------------------------------------------------------------------------------------------

void FrameBuffer::generateTexture(GLuint &texture,GLuint internalFormat,GLuint format, GLuint type, bool border) const {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width_, height_, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if(border)
    {
        //Border color
        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
}

void FrameBuffer::addTexture(GLuint internalFormat, GLuint format, GLuint type, bool border, GLuint attachment) {
    //Bind
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
    //Texture creation
    GLuint texture;
    generateTexture(texture, internalFormat, format, type,border);
    //Attach to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
    //Unbind
    glBindFramebuffer(GL_FRAMEBUFFER, default_fbo);
    textures_.push_back(texture);
}

void FrameBuffer::addColorTexture() {
    if (num_color > GL_COLOR_ATTACHMENT31) return;
    addTexture(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE,false,GL_COLOR_ATTACHMENT0 + num_color++);
}

void FrameBuffer::addDepthTexture() {
    if (depth_) return;
    addTexture(GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT, GL_FLOAT,true,GL_DEPTH_ATTACHMENT);
    depth_ = true;

}

void FrameBuffer::addStencilTexture() {
    if (stencil_) return;
    addTexture(GL_STENCIL_INDEX, GL_STENCIL_INDEX,GL_INT,true,GL_STENCIL_ATTACHMENT);
    stencil_ = true;
}

void FrameBuffer::addDepthStencilTexture() {
    if (stencil_depth) return;
    addTexture(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,true,GL_DEPTH_STENCIL_ATTACHMENT);
    stencil_depth = true;
}








