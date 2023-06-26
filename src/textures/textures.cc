#include "textures.hh"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>


Texture::Texture(const std::string& path)
    : textureID_(0), filepath_(path), buffer_(nullptr), width_(0), height_(0), bpp_(0)
{
    stbi_set_flip_vertically_on_load(1);
    this->buffer_ = stbi_load(path.c_str(), &this->width_, &this->height_, &this->bpp_, 4);

    if (!this->buffer_)
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}

    glGenTextures(1, &this->textureID_);
    glBindTexture(GL_TEXTURE_2D, this->textureID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width_, this->height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->buffer_);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (this->buffer_) 
    {
        stbi_image_free(this->buffer_);
    }
}

Texture::~Texture() 
{
    glDeleteTextures(1, &this->textureID_);
}

void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->textureID_);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
