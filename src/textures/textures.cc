#include "textures.hh"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)


Texture::Texture(const std::string& path)
    : textureID_(0), filepath_(path), buffer_(nullptr), width_(0), height_(0), bpp_(0)
{
    stbi_set_flip_vertically_on_load(1);
    this->buffer_ = stbi_load(path.c_str(), &this->width_, &this->height_, &this->bpp_, 4);

    if (!this->buffer_)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}

    GL_CALL(glGenTextures(1, &this->textureID_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, this->textureID_));

    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width_, this->height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->buffer_));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    if (this->buffer_) 
    {
        stbi_image_free(this->buffer_);
    }
}

Texture::~Texture() 
{
    GL_CALL(glDeleteTextures(1, &this->textureID_));
}

void Texture::bind(unsigned int slot) const 
{
   GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
   GL_CALL(glBindTexture(GL_TEXTURE_2D, this->textureID_));
}

void Texture::unbind() const 
{
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
