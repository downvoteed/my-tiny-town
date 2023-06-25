#pragma once
#include <glm/glm.hpp>
#include <string>
#include "textures/textures.hh"

/**
 * @brief Interface for all models.
 */
class Model 
{
public:
    /**
     * @brief Construct a new Model object. 	
	 * @param texturePath 
	 * @param position 
	 * @param size 
	 * @param rotation 
	 .
     */
    Model(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation) : 
        texture_(texturePath), position_(position), size_(size), rotation_(rotation) {}
    virtual ~Model() = default;

    /**
     * @brief set the position of the model.
     */
    virtual void setPosition(const glm::vec3& position)
    {
        this->position_ = position;
    }
    /**
	 * @brief set the size of the model.
	 */
    virtual void setSize(const glm::vec3& size)
    {
        this->size_ = size;
    }
    /**
     * @brief set the rotation of the model.
     */
    virtual void setRotation(const float rotation)
    {
        this->rotation_ = rotation;
    }
    /**
     * @brief get the position of the model.
     */
    virtual glm::vec3 getPosition() const
    {
        return this->position_;
    }
    /**
     * @brief set the projection matrix of the model.
     */
    virtual void setProjectionMatrix(const glm::mat4& projectionMatrix)
    {
        this->projectionMatrix_ = projectionMatrix;
    }
    /**
	 * @brief set the view matrix of the model.
	 */
    virtual void setViewMatrix(const glm::mat4& viewMatrix)
    {
        this->viewMatrix_ = viewMatrix;
    }
    /**
	 * @brief get the size of the model.
	 */
    virtual glm::vec3 getSize()
    {
        return this->size_;
    }
    /**
	 * @brief get the rotation of the model.
	 */
    virtual float getRotation() const
    {
        return this->rotation_;
    }
    /**
     * @brief get projection matrix of the model.
     */
    virtual glm::mat4 getProjectionMatrix() const
	{
		return this->projectionMatrix_;
	}
    /**
	 * @brief get view matrix of the model.
	 */
	virtual glm::mat4 getViewMatrix() const
	{
		return this->viewMatrix_;
	}
    /**
	 * @brief draw the model.
	 */
    virtual void draw() const = 0;

private:
    Texture texture_;
    glm::vec3 position_;
    glm::vec3 size_;
    float rotation_;
    glm::mat4 projectionMatrix_;
	glm::mat4 viewMatrix_;
};

