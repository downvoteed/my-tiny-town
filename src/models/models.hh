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
#include "objloader.hh"
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
	Model(std::string name, const std::string& modelPath, const glm::vec3& position, const glm::vec3& size, float rotation) :
		name_(name), position_(position), size_(size), rotation_(rotation)
	{
		this->initModel(position, size);
		this->buildObjModel(modelPath);
	}
	Model(std::string name, const glm::vec3& position, const glm::vec3& size, float rotation) :
		name_(name), position_(position), size_(size), rotation_(rotation)
	{
		this->initModel(position, size);
	}
	virtual ~Model() = default;


	virtual void buildObjModel(const std::string modelPath)
	{
		ObjLoader objloader(modelPath);
		auto vertices = objloader.getVertices();
		auto texCoords = objloader.getTexCoords();
		auto normals = objloader.getNormals();

		std::vector<float> interleavedData;
		interleavedData.reserve(vertices.size() * 8); // x,y,z,nx,ny,nz,u,v for each vertex

		for (size_t i = 0; i < vertices.size(); ++i)
		{
			// vertex coordinates
			interleavedData.push_back(vertices[i].x);
			interleavedData.push_back(vertices[i].y);
			interleavedData.push_back(vertices[i].z);

			// texture coordinates
			interleavedData.push_back(texCoords[i].x);
			interleavedData.push_back(texCoords[i].y);

			// normal coordinates
			interleavedData.push_back(normals[i].x);
			interleavedData.push_back(normals[i].y);
			interleavedData.push_back(normals[i].z);
		}
		// Create the Vertex Buffer and the Vertex Array Object
		this->va_ = std::make_unique<VertexArray>();
		this->va_->bind();
		this->vb_ = std::make_unique<VertexBuffer>(interleavedData.data(), interleavedData.size() * sizeof(float));
		this->ib_ = std::make_unique<IndexBuffer>(objloader.getIndices().data(), objloader.getIndices().size());

		VertexBufferLayout layout;
		layout.push<float>(3); // Push 3 floats for position
		layout.push<float>(2); // Push 2 floats for texture coordinates
		layout.push<float>(3); // Push 3 floats for normal

		this->va_->addBuffer(*this->vb_, layout);


		this->va_->unbind();
	}

	virtual void rotate(float angle, const glm::vec3& axis)
	{
		this->modelMatrix_ = glm::rotate(this->modelMatrix_, angle, axis);
	}

	/**
	 * @brief set the position of the model.
	 */
	virtual void setPosition(const glm::vec3& position)
	{
		this->modelMatrix_[3] = glm::vec4(position, 1.0f);
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
		return this->modelMatrix_[3];
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
	virtual void draw(bool isPicking) = 0;

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
		if (!this->isSelected_) { return; }

		this->shader_->bind();

		GL_CALL(glEnable(GL_STENCIL_TEST));
		// Tous les fragments doivent passer le test de stencil
		GL_CALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		// Les fragments qui passent le test de profondeur remplacent la valeur du  stencil buffer
		GL_CALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
		// Active l'écriture dans le stencil
		GL_CALL(glStencilMask(0xFF));

		this->draw(false);

		this->shader_->unbind();
	}
	virtual void drawOutline()
{
    if (!this->isSelected_) { return; }

    this->outlineShader_->bind();

    GL_CALL(glEnable(GL_STENCIL_TEST));
    GL_CALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GL_CALL(glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP));
    GL_CALL(glStencilMask(0x00));
    GL_CALL(glDisable(GL_DEPTH_TEST));

    glm::mat4 view = this->getViewMatrix();
    glm::mat4 projection = this->getProjectionMatrix();

    this->outlineShader_->setUniformMat4f("model", this->modelMatrix_);
    this->outlineShader_->setUniformMat4f("view", view);
    this->outlineShader_->setUniformMat4f("projection", projection);

    // Calculer l'échelle à partir de la matrice de modèle
    glm::vec3 scale = glm::vec3(glm::length(this->modelMatrix_[0]), glm::length(this->modelMatrix_[1]), glm::length(this->modelMatrix_[2]));

    // Utiliser l'échelle pour ajuster l'épaisseur du contour
    float outlineThickness = 0.1 / glm::length(scale);
    this->outlineShader_->setUniform1f("outlineThickness", outlineThickness);

    this->va_->bind();
    this->vb_->bind();
    this->ib_->bind();

    GL_CALL(glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr));

    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glStencilMask(0xFF));
    GL_CALL(glDisable(GL_STENCIL_TEST));

    this->va_->unbind();
    this->vb_->unbind();
    this->ib_->unbind();

    this->outlineShader_->unbind();
}


	/**
	 * @brief get the name of the model.
	 */

	const std::string& getName()
	{
		return this->name_;
	}

	const std::string& getTextureName()
	{
		return this->textureName_;
	}

protected:
	float rotation_;
	glm::mat4 projectionMatrix_;
	glm::mat4 viewMatrix_;
	glm::mat4 modelMatrix_;
	std::unique_ptr<VertexBuffer> vb_;
	std::unique_ptr<IndexBuffer> ib_;
	std::unique_ptr<VertexArray> va_;
	std::unique_ptr<Texture> texture_;
	std::unique_ptr<Shader> shader_;
	std::unique_ptr<Shader> outlineShader_;
	glm::vec3 position_;
	glm::vec3 size_;
	glm::vec3 vertices_;
	std::string textureName_;
	glm::vec3 textCoords_;
	glm::vec3 normals_;

private:

	virtual void initModel(const glm::vec3& position, const glm::vec3 size)
	{
		this->outlineShader_ = std::make_unique<Shader>("assets/shaders/outline-vertex.glsl", "assets/shaders/outline-fragment.glsl");
		this->modelMatrix_ = glm::mat4(1.0f);
		this->modelMatrix_ = glm::translate(this->modelMatrix_, position);
		this->modelMatrix_ = glm::scale(this->modelMatrix_, size); // scale the plane
		this->modelMatrix_ = glm::rotate(this->modelMatrix_, glm::radians(this->rotation_), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ID_ = ++current_ID;
	}

	std::string name_;
	bool isSelected_ = false;
	size_t ID_;
};

