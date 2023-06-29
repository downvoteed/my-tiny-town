#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>
#include "textures/textures.hh"
#include "vertex-buffer.hh"
#include "vertex-array.hh"
#include "shader.hh"
#include "index-buffer.hh"
#include <iostream>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

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
		this->outlineShader_ = std::make_unique<Shader>("assets/shaders/outline-vertex.glsl", "assets/shaders/outline-fragment.glsl");
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

    virtual void drawStencil()
    {
		this->outlineShader_->bind();

		if (!this->isSelected_) { return; }
		GL_CALL(glEnable(GL_STENCIL_TEST));
		GL_CALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		GL_CALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)); // Les fragments qui passent le test de profondeur remplacent la valeur du tampon de stencil
		GL_CALL(glStencilMask(0xFF)); // Active l'écriture dans le tampon de stencil

		GL_CALL(glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE));

        this->outlineShader_->unbind();
    }

    virtual void drawOutline()
    {
        if (!this->isSelected_) { return; }

        this->outlineShader_->bind();
		// Disable writing to the color buffer

		GL_CALL(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE));

		// Enable stencil testing
		glEnable(GL_STENCIL_TEST);

		// Configure the stencil test to pass only when the stencil value is 1
		GL_CALL(glStencilFunc(GL_EQUAL, 1, 0xFF));

		// Disable writing to the stencil buffer
		GL_CALL(glStencilMask(0x00));



        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = this->getViewMatrix();
		glm::mat4 projection = this->getProjectionMatrix();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f)); // move the plane in front of the camera
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f)); // scale the plane

		outlineShader_->setUniformMat4f("model", model);
		outlineShader_->setUniformMat4f("view", view);
		outlineShader_->setUniformMat4f("projection", projection);
        outlineShader_->setUniform1f("outlineThickness", 3);

		// Bind the vertex array object
		this->va_->bind();
		this->vb_->bind();
		this->ib_->bind();

		GL_CALL(glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr));

		GL_CALL(glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE));

		glDisable(GL_STENCIL_TEST);

        this->va_->unbind();
        this->vb_->unbind();
        this->ib_->unbind();

		this->outlineShader_->unbind();
        
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
	std::unique_ptr<Shader> outlineShader_;
	glm::vec3 position_;
	glm::vec3 size_;
	std::string texturePath_;
};

