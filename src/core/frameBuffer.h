//
// Created by robin on 23/10/2020.
//

#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H
#include <opengl_stuff.h>
#include <vector>

class FrameBuffer {
public:

    FrameBuffer(int t_width, int t_height, int t_numSamples)
            : m_width{t_width}, m_height{t_height}, m_num_samples(t_numSamples)
            {
                glGenFramebuffers(1, &m_fbo);



            }

    ~FrameBuffer();

    void use() const;

    void stop(int width, int height) const;

    [[nodiscard]] const std::vector<GLuint> &textures() const { return m_textures; }

    [[nodiscard]] const std::vector<GLuint> &buffers() const { return m_buffers; }

    static void setDefaultFbo(GLuint t_numFbo){ s_default_fbo = t_numFbo;}


private:
    void addBuffer(GLuint t_format, GLuint t_attachment);
    void generateTexture(GLuint &t_texture, GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border) const;
    void addTexture(GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border, GLuint t_attachment);

public:
    void drawBuffers() const;
    void addColorBuffer();
    void addDepthBuffer();
    void addStencilBuffer();
    void addDepthStencilBuffer();
    void addColorTexture();
    void addDepthTexture();
    void addStencilTexture();
    void addDepthStencilTexture();


private:
    static GLuint s_default_fbo;
    int m_num_samples;
    int m_width, m_height;
    GLuint m_fbo;
    std::vector<GLuint> m_textures;
    std::vector<GLuint> m_buffers;

    bool m_is_stencil{false};
    bool m_is_depth{false};
    bool m_is_stencil_depth{false};
    int m_num_color{0};
};


#endif //ENGINE_FRAMEBUFFER_H
