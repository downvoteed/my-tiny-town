#include "grass-plane-model.hh"
#include "vertex-buffer.hh"
#include "vertex-buffer-layout.hh"
#include "index-buffer.hh"
#include "shader.hh"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <iostream>

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
	this->va_ = std::make_unique<VertexArray>();
	this->va_->bind();
    this->vb_ = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    this->ib_ = std::make_unique<IndexBuffer>(indices, 6);

	VertexBufferLayout layout;
    layout.push<float>(3); // Push 3 floats for position
    layout.push<float>(2); // Push 2 floats for texture coordinates

	this->va_->addBuffer(*this->vb_, layout);


    // Load the texture
    this->texture_ = std::make_unique<Texture>(texturePath);

    // Create the shader
    this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

	this->va_->unbind();
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

	// view matrix
	glm::mat4 view = glm::mat4(1.0f); // keep the camera at the origin

	// projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.f);

	// model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f)); // move the plane in front of the camera

	// set uniforms
	this->shader_->setUniformMat4f("model", model);
	this->shader_->setUniformMat4f("view", view);
	this->shader_->setUniformMat4f("projection", projection);

	// Bind the shader
	this->shader_->bind();

	// Set the textureSampler uniform to the texture unit
	this->shader_->setUniform1i("textureSampler", 0); // 0 is the texture unit

	// Bind the texture
	this->texture_->bind(0); // 0 is the texture unit

	// Bind the vertex array object
	this->vb_->bind();
	this->ib_->bind();
	this->va_->bind();

	// Draw the model
	glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr);
	// Check for OpenGL errors
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "OpenGL error: " << err << std::endl;
    }
}

