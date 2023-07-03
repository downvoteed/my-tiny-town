#include "frame-buffer.hh"
#include "ui/application.hh"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

FrameBuffer::FrameBuffer(bool useDepth)
{
    // Generate and bind the framebuffer
    GL_CALL(glGenFramebuffers(1, &fbo_));
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo_));

    // Generate the texture
    GL_CALL(glGenTextures(1, &texture_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture_));

    // Set the texture parameters
    GLFWwindow* window = Application::instance()->getWindow();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    if (useDepth)
    {
        // Create a depth texture
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
             width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        GL_CALL(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor)); 

        // Attach the depth texture to the framebuffer
        GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_, 0));
        GL_CALL(glDrawBuffer(GL_NONE));
        GL_CALL(glReadBuffer(GL_NONE));
    }
    else
    {
        // Create a color texture
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        // Attach the color texture to the framebuffer
        GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0));
    }

    // Check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Error : Framebuffer is not complete" << std::endl;

    // Unbind the framebuffer and texture
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}



FrameBuffer::~FrameBuffer()
{
    GL_CALL(glDeleteTextures(1, &texture_));
    GL_CALL(glDeleteFramebuffers(1, &fbo_));
}

void FrameBuffer::bind() const 
{
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo_));
}

void FrameBuffer::unbind() const 
{
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

GLuint FrameBuffer::getTexture() const 
{
    return texture_;
}

