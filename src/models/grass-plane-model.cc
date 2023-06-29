#include "grass-plane-model.hh"
#include "vertex-buffer.hh"
#include "vertex-buffer-layout.hh"
#include "index-buffer.hh"
#include "shader.hh"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "utils/utils.hh"
#include <memory>
#include <iostream>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)


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
	this->armTexture_ = std::make_unique<Texture>("assets/textures/arm/grass-plane.jpg");
	this->diffTexture_ = std::make_unique<Texture>(texturePath);


    // Create the shader
    this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/grass-plane-fragment.glsl");

	this->va_->unbind();
}

void GrassPlane::draw(bool isPicking) const
{
	// Bind the shader
	this->shader_->bind();

	glm::mat4 view = this->getViewMatrix();
	glm::mat4 projection = this->getProjectionMatrix();

	// model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f)); 
	model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f)); 

	// set uniforms
	this->shader_->setUniformMat4f("model", model);
	this->shader_->setUniformMat4f("view", view);
	this->shader_->setUniformMat4f("projection", projection);

	// Bind the texture
	armTexture_->bind(0);
    diffTexture_->bind(1);

	shader_->setUniform1i("armTexture", 0);
	shader_->setUniform1i("diffTexture", 1);
	// Bind the vertex array object
	this->va_->bind();
	this->vb_->bind();
	this->ib_->bind();

	// generator unique color from ID for FBO object picking
	glm::vec3 uniqueColor = idToColor(this->getID()); 
	this->shader_->setUniform3f("objectColor", uniqueColor.r, uniqueColor.g, uniqueColor.b);

	if (isPicking)
		this->shader_->setUniform1i("isPicking", 1);
	else
		this->shader_->setUniform1i("isPicking", 0);

	// Draw the model
	GL_CALL(glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr));

	this->shader_->setUniform1i("isPicking", 0);

	this->shader_->unbind();
	this->va_->unbind();
	this->vb_->unbind();
	this->ib_->unbind();
}

