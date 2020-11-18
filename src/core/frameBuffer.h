//
// Created by robin on 23/10/2020.
//

#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H
#include <opengl_stuff.h>
#include <vector>

class FrameBuffer {
public:
    /**
     * Constructor
     * Generate a frameBuffer object with no attachments
     * @param t_width
     * @param t_height
     * @param t_numSamples
     */
    FrameBuffer(int t_width, int t_height, int t_numSamples)
            : m_width{t_width}, m_height{t_height}, m_num_samples(t_numSamples)
            {
                glGenFramebuffers(1, &m_fbo);
            }
    /**
     * Destructor
     * Remove textures,buffers and the frameBuffer object
     */
    ~FrameBuffer();
    /**
     * Bind FrameBuffer object and reset viewport
     */
    void use() const;
    /**
     * Debind FrameBufferObject and reset viewport with arguments width and height
     * @param width
     * @param height
     */
    void stop(int width, int height) const;
    /**
     * Copy this FrameBuffer's Depth Buffer to the FrameBuffer in parameters
     * @param t_write_from
     */
    void copyDepthBuffer(FrameBuffer &t_write_from);
    /**
     * Textures getter
     * @return textures vector
     */
    [[nodiscard]] const std::vector<GLuint> &textures() const { return m_textures; }
    /**
     * Buffers getter
     * @return buffers vector
     */
    [[nodiscard]] const std::vector<GLuint> &buffers() const { return m_buffers; }
    /**
     * Static func to set the default screen fbo from QT::defaultFrameBufferObject()
     * @param t_numFbo
     */
    static void setDefaultFbo(GLuint t_numFbo){ s_default_fbo = t_numFbo;}
    /**
     * Are the color attachments cube maps textures
     * @return
     */
    bool isCubeMap(){return m_is_cube_map;}


private:
    /**
     * Refactoring
     * Add a buffer with given format and attachment
     * @param t_format
     * @param t_attachment
     */
    void addBuffer(GLuint t_format, GLuint t_attachment);
    /**
     * Refactoring
     * Generate a texture with given id, internal format, format, type and border or not
     * @param t_texture
     * @param t_internalFormat
     * @param t_format
     * @param t_type
     * @param t_border
     */
    void generateTexture(GLuint &t_texture, GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border) const;
    /**
     * Add a Texture with given internal format, format, type, attachment and border or not
     * @param t_internalFormat
     * @param t_format
     * @param t_type
     * @param t_border
     * @param t_attachment
     */
    void addTexture(GLuint t_internalFormat, GLuint t_format, GLuint t_type, bool t_border, GLuint t_attachment);

public:
    /**
     * Draw color buffers
     */
    void drawBuffers() const;
    /**
     * Add a Color Buffer
     */
    void addColorBuffer();
    /**
     * Add a Depth Buffer
     */
    void addDepthBuffer();
    /**
     * Add a Stencil Buffer
     */
    void addStencilBuffer();
    /**
     * Add a Depth and Stencil Buffer
     */
    void addDepthStencilBuffer();
    /**
     * Add a Color Texture
     */
    void addColorTexture();
    /**
     * Add a Depth Texture
     */
    void addDepthTexture();
    /**
     * Add a Stencil Texture
     */
    void addStencilTexture();
    /**
     * Add a Depth and Stencil Texture
     */
    void addDepthStencilTexture();
    /**
     * Add a Depth Cube Map
     */
    void addDepthCubeMap();



private:
    static GLuint s_default_fbo;    //Default screen fbo, statically setup from QT::defaultFrameBufferObject()
    int m_num_samples;  //Number of samples in case of multisampling
    int m_width, m_height; //Width and Height of the attachment
    GLuint m_fbo; //Fbo id
    std::vector<GLuint> m_textures; //Vector of attached textures
    std::vector<GLuint> m_buffers; //Vector of attached buffers

    bool m_is_stencil{false};
    bool m_is_depth{false};
    bool m_is_stencil_depth{false};
    bool m_is_cube_map{false};
    int m_num_color{0};  //Number of color attachements
};


#endif //ENGINE_FRAMEBUFFER_H
