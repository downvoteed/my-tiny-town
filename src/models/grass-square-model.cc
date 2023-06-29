#include "grass-square-model.hh"
#include <iostream>
#include "utils/objloader.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "utils/utils.hh"
#include <vector>

GrassSquare::GrassSquare(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation)
    : Model(texturePath, position, size, rotation) {
    // Create the plane model


	ObjLoader objloader("assets/models/grass-square.obj");
	auto vertices = objloader.getVertices();
	auto texCoords = objloader.getTexCoords();

	std::vector<float> interleavedData;
	interleavedData.reserve(vertices.size() + texCoords.size());

	for (size_t i = 0; i < vertices.size() / 3; ++i) 
	{
		interleavedData.push_back(vertices[i].x);
		interleavedData.push_back(vertices[i].y);
		interleavedData.push_back(vertices[i].z);

		interleavedData.push_back(texCoords[i].x);
		interleavedData.push_back(texCoords[i].y);
	}


    // Create the Vertex Buffer and the Vertex Array Object
	this->va_ = std::make_unique<VertexArray>();
	this->va_->bind();
	this->vb_ = std::make_unique<VertexBuffer>(interleavedData.data(), interleavedData.size() * sizeof(float));
	this->ib_ = std::make_unique<IndexBuffer>(objloader.getIndices().data(), objloader.getIndices().size());


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

void GrassSquare::draw(bool isPicking) const
{
	// Bind the shader
	this->shader_->bind();

	glm::mat4 view = this->getViewMatrix();
	glm::mat4 projection = this->getProjectionMatrix();

	// model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f)); // move the plane in front of the camera
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f)); // scale the plane


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
	glDrawElements(GL_TRIANGLES, this->ib_->getCount(), GL_UNSIGNED_INT, nullptr);

	this->shader_->setUniform1i("isPicking", 0);

	// Check for OpenGL errors
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "OpenGL error: " << err << std::endl;
	}
}