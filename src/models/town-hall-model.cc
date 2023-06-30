#include "town-hall-model.hh"
#include <iostream>
#include "utils/objloader.hh"
#include "utils/utils.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

TownHall::TownHall(std::string name, const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation)
    : Model(name, texturePath, position, size, rotation) {
    // Create the plane model

	this->modelMatrix_ = glm::rotate(this->modelMatrix_, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	ObjLoader objloader("assets/models/b.obj");
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
	layout.push<float>(3); // Push 3 floats for normals

	this->va_->addBuffer(*this->vb_, layout);

    // Load the texture
    this->texture_ = std::make_unique<Texture>(texturePath);

    // Create the shader
    this->shader_ = std::make_unique<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

	this->va_->unbind();
}

void TownHall::draw(bool isPicking) 
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
