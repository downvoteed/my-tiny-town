#pragma once
#include <string>

class Texture {
public:
    /**
    * @brief Construct a new Texture object
    */
    Texture(const std::string& path);
	~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture(Texture&& other) noexcept = delete;
	Texture& operator=(Texture&& other) noexcept = delete;

    /**
    * @brief Bind the texture to the current context
    */
    void bind(unsigned int slot = 0) const;
    /**
    * @brief Unbind the texture from the current context
	*/
    void unbind() const;

    /** 
    * @brief Get the width of the texture
    */
    inline int getWidth() const { return this->width_; }
    /**
    * @brief Get the height of the texture
	*/
    inline int getHeight() const { return this->height_; }

private:
    unsigned int textureID_;
    std::string filepath_;
    unsigned char* buffer_;
    int width_;
    int height_;
    int bpp_;
};
