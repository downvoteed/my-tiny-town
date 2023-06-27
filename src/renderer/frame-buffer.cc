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


FrameBuffer::FrameBuffer()
{
    // Generate and bind the framebuffer
    GL_CALL(glGenFramebuffers(1, &fbo_));
    GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, fbo_));

    // Generate the texture
    GL_CALL(glGenTextures(1, &texture_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture_));

    // Set the texture parameters
    // FIXME : not sure about dimensions
    GLFWwindow* window = Application::instance()->getWindow();
    int width, height;
	GL_CALL(glfwGetFramebufferSize(window, &width, &height));

    std::cout << "width : " << width - Application::instance()->getPannelLeftWidth() << std::endl;
    std::cout << "height : " << height << std::endl;
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width - Application::instance()->getPannelLeftWidth(), height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    // Attach the texture to the framebuffer
    GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_, 0));

    glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (! glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
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