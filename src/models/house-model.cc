#include "house-model.hh"
#include <iostream>
#include "utils/objloader.hh"
#include "utils/utils.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

House::House(std::string name, const std::string& modelPath, const std::string& texturePath,
	const glm::vec3& position, const glm::vec3& size, float rotation)
	: Model(name, modelPath, position, size, rotation)
{
	// Load the texture
	this->texture_ = std::make_unique<Texture>(texturePath);
	this->textureName_ = texturePath.substr(texturePath.find_last_of("/\\") + 1);

	// Create the shader
	this->shader_ = std::make_unique<Shader>("assets/shaders/lightning-vertex.glsl",
		"assets/shaders/lightning-fragment.glsl");
}

void House::draw(bool isPicking)
{
	this->shader_->bind();

	glm::mat4 view = this->getViewMatrix();
	glm::mat4 projection = this->getProjectionMatrix();

	this->shader_->setUniformMat4f("model", this->modelMatrix_);
	this->shader_->setUniformMat4f("view", view);
	this->shader_->setUniformMat4f("projection", projection);

	// Set light source position
	glm::vec3 lightPos(0.0f, 50.0f, 100.0f);
	this->shader_->setUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

	this->shader_->setUniform1i("textureSampler", 0);
	this->texture_->bind(0);

	this->va_->bind();
	this->vb_->bind();
	this->ib_->bind();

	glm::vec3 uniqueColor = idToColor(this->getID());
	this->shader_->setUniform3f("objectColor", uniqueColor.r, uniqueColor.g, uniqueColor.b);

	if (isPicking)
		this->shader_->setUniform1i("isPicking", 1);
	else
		this->shader_->setUniform1i("isPicking", 0);

	glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr);

	this->shader_->setUniform1i("isPicking", 0);

	this->shader_->unbind();
}



void House::rotate(float angle, const glm::vec3& axis)
{
	glm::vec3 newAxis = glm::vec3(axis.x, axis.y, axis.z);
	this->modelMatrix_ = glm::rotate(this->modelMatrix_, angle, newAxis);
}
