#pragma once
#include "models/models.hh"
#include "vertex-buffer.hh"
#include "vertex-array.hh"
#include "index-buffer.hh"
#include "textures.hh"
#include "shader.hh"
#include <memory>

class GrassPlane : public Model {
public:
    GrassPlane(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation);
	~GrassPlane() override = default;

    void draw() const override;
    
private:
	std::unique_ptr<VertexBuffer> vb_;
	std::unique_ptr<IndexBuffer> ib_;
	std::unique_ptr<VertexArray> va_;
	std::unique_ptr<Texture> texture_;
	std::unique_ptr<Shader> shader_;
	glm::vec3 position_;
	glm::vec3 size_;
	float rotation_;
	std::string texturePath_;
};

