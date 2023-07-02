#include "grass-square-model.hh"
#include <iostream>
#include "utils/objloader.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/utils.hh"
#include <vector>

#define GL_CALL(x) \
    do { \
        x; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) { \
            std::cerr << "OpenGL error " << error << " at " << __FILE__ << ":" << __LINE__ << " - for " << #x << std::endl; \
        } \
    } while (0)

GrassSquare::GrassSquare(std::string name, const std::string& modelPath, const std::string& texturePath,
	const glm::vec3& position, const glm::vec3& size, float rotation)
	: Model(name, modelPath, position, size, rotation)
{
	// Load the texture
	this->texture_ = std::make_unique<Texture>(texturePath);
	this->textureName_ = texturePath.substr(texturePath.find_last_of("/\\") + 1);

	// Create the shader
	this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void GrassSquare::draw(bool isPicking)
{
	// Bind the shader
	this->shader_->bind();

	glm::mat4 view = this->getViewMatrix();
	glm::mat4 projection = this->getProjectionMatrix();

	// set uniforms
	this->shader_->setUniformMat4f("model", this->modelMatrix_);
	this->shader_->setUniformMat4f("view", view);
	this->shader_->setUniformMat4f("projection", projection);

	// Set the textureSampler uniform to the texture unit
	this->shader_->setUniform1i("textureSampler", 0); // 0 is the texture unit

	// Bind the texture
	this->texture_->bind(0); // 0 is the texture unit

	// Bind the vertex array object
	this->va_->bind();
	this->vb_->bind();
	this->ib_->bind();

	// generator unique color from ID for FBO object picking
	glm::vec3 uniqueColor = idToColor(this->getID());
	this->shader_->setUniform3f("objectColor", uniqueColor.r, uniqueColor.g, uniqueColor.b);
	this->shader_->setUniform1i("isPicking", 1);
	if (isPicking)
		this->shader_->setUniform1i("isPicking", 1);
	else
		this->shader_->setUniform1i("isPicking", 0);

	// Draw the model
	GL_CALL(glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr));

	this->shader_->setUniform1i("isPicking", 0);


	this->va_->unbind();
	this->vb_->unbind();
	this->ib_->unbind();

	this->shader_->unbind();
}

void GrassSquare::rotate(float angle, const glm::vec3& axis)
{
	glm::vec3 newAxis = glm::vec3(axis.x, axis.z, axis.y);
	this->modelMatrix_ = glm::rotate(this->modelMatrix_, angle, newAxis);
}
