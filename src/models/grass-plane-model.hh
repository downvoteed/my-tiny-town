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
    void setPosition(const glm::vec3& position) override;

    void setSize(const glm::vec3& size) override;

    void setRotation(float rotation) override;

    glm::vec3 getPosition() const override;
    glm::vec3 getSize() const override;

    float getRotation() const override;
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

