#pragma once
#include <glm/glm.hpp>
#include <string>
#include "textures/textures.hh"

// TODO: add documentation
//TODO : implement the function members	
class Model 
{
public:
    Model(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation) : 
        texture_(texturePath), position_(position), size_(size), rotation_(rotation) {}
    virtual ~Model() = default;

	virtual void setPosition(const glm::vec3& position) = 0;
	virtual void setSize(const glm::vec3& size) = 0;
	virtual void setRotation(float rotation) = 0;

    virtual glm::vec3 getPosition() const = 0;
    virtual glm::vec3 getSize() const = 0;
    virtual float getRotation() const = 0;

    virtual void draw() const = 0;

private:
    Texture texture_;
    glm::vec3 position_;
    glm::vec3 size_;
    float rotation_;
};

