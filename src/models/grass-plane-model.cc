#include "grass-plane-model.hh"
#include "vertex-buffer.hh"
#include "index-buffer.hh"
#include "shader.hh"
#include "glad/glad.h"
#include <memory>

GrassPlane::GrassPlane(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation)
    : Model(texturePath, position, size, rotation) {
    // Create the plane model
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create the Vertex Buffer and the Vertex Array Object
    this->vb_ = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->ib_ = std::make_unique<IndexBuffer>(indices, sizeof(indices));

    // Load the texture
    this->texture_ = std::make_unique<Texture>(texturePath);

    // Create the shader
    this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void GrassPlane::setPosition (const glm::vec3& position) 
{
	this->position_ = position;
}
void GrassPlane::setRotation (float rotation) 
{
	this->rotation_ = rotation;
}

void GrassPlane::setSize (const glm::vec3& size) 
{
	this->size_ = size;
}

glm::vec3 GrassPlane::getPosition () const
{
	return this->position_;
}

float GrassPlane::getRotation () const
{
	return this->rotation_;
}

glm::vec3 GrassPlane::getSize () const
{
	return this->size_;
}

void GrassPlane::draw () const
{
	// Bind the shader
	this->shader_->bind();

	// Bind the texture
	this->texture_->bind();

	// Bind the vertex array object
	this->vb_->bind();
	this->ib_->bind();

	// Draw the model
	glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr);
}
