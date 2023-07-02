#include "building-model.hh"
#include <iostream>
#include "utils/objloader.hh"
#include "utils/utils.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

Building::Building(std::string name, const std::string& modelPath, const std::string& texturePath, 
	const glm::vec3& position, const glm::vec3& size, float rotation)
    : Model(name, modelPath , position, size, rotation) 
{
	// Load the texture
	this->texture_ = std::make_unique<Texture>(texturePath);
	this->textureName_ = texturePath.substr(texturePath.find_last_of("/\\") + 1);
	this->modelMatrix_ = glm::rotate(this->modelMatrix_, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	// Create the shader
	this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void Building::draw(bool isPicking) 
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

	if (isPicking)
		this->shader_->setUniform1i("isPicking", 1);
	else
		this->shader_->setUniform1i("isPicking", 0);

	// Draw the model
	glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr);

	this->shader_->setUniform1i("isPicking", 0);

	this->shader_->unbind();
}

void Building::rotate(float angle, const glm::vec3& axis) 
{
	glm::vec3 newAxis = glm::vec3(axis.x, axis.y, axis.z);
	this->modelMatrix_ = glm::rotate(this->modelMatrix_, angle, newAxis);
}
