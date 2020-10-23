//
// Created by robin on 23/10/2020.
//

#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H
#include <glad/GLAD-Includes/gl46core/glad.h>
#include <vector>

class FrameBuffer {
public:

    FrameBuffer(int width, int height, int numSamples)
            : width_{width}, height_{height}, num_samples(numSamples)
            {
                glGenFramebuffers(1, &fbo_);
            }

    ~FrameBuffer();

    void use() const;

    void stop(int width, int height) const;

    [[nodiscard]] const std::vector<GLuint> &textures() const { return textures_; }

    [[nodiscard]] const std::vector<GLuint> &buffers() const { return buffers_; }

    static void setDefaultFbo(GLuint fbo) { default_fbo = fbo; }

private:
    void addBuffer(GLuint format,GLuint attachment);
    void generateTexture(GLuint texture,GLuint internalFormat,GLuint format, GLuint type, bool border) const;
    void addTexture(GLuint internalFormat,GLuint format, GLuint type, bool border, GLuint attachment);
    void drawBuffers() const;
public:
    void addColorBuffer();
    void addDepthBuffer();
    void addStencilBuffer();
    void addDepthStencilBuffer();
    void addColorTexture();
    void addDepthTexture();
    void addStencilTexture();
    void addDepthStencilTexture();


private:
    static GLuint default_fbo;
    int num_samples;
    int width_, height_;
    GLuint fbo_{0};
    std::vector<GLuint> textures_;
    std::vector<GLuint> buffers_;

    bool stencil_{false};
    bool depth_{false};
    bool stencil_depth{false};
    int num_color{0};
};


#endif //ENGINE_FRAMEBUFFER_H
