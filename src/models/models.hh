#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include "textures/textures.hh"
#include "vertex-buffer.hh"
#include "vertex-array.hh"
#include "shader.hh"
#include "index-buffer.hh"

/**
 * @brief Interface for all models.
 */
class Model 
{
public:
    static size_t current_ID;
    /**
     * @brief Construct a new Model object. 	
	 * @param texturePath 
	 * @param position 
	 * @param size 
	 * @param rotation 
	 .
     */
    Model(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation) : 
        position_(position), size_(size), rotation_(rotation) 
    {
		this->texture_ = std::make_unique<Texture>(texturePath);
        this->ID_ = ++current_ID;
    }
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
    virtual void draw(bool isPicking) const = 0;

    /**
     *  @brief return object ID.
     */
    virtual size_t getID() const
    {
        return this->ID_;
    }

    virtual bool isSelected() const
    {
        return this->isSelected_;
    }

    virtual void setSelected(bool b)
	{
		this->isSelected_ = b;
	}

protected:
    bool isSelected_ = false;
    size_t ID_;
    float rotation_;
    glm::mat4 projectionMatrix_;
	glm::mat4 viewMatrix_;
	std::unique_ptr<VertexBuffer> vb_;
	std::unique_ptr<IndexBuffer> ib_;
	std::unique_ptr<VertexArray> va_;
	std::unique_ptr<Texture> texture_;
	std::unique_ptr<Shader> shader_;
	glm::vec3 position_;
	glm::vec3 size_;
	std::string texturePath_;
};

