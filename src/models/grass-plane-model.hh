#pragma once
#include "models/models.hh"
#include "textures.hh"
#include "shader.hh"
#include <memory>

class GrassPlane : public Model {
public:
	GrassPlane(std::string name, const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation);
	~GrassPlane() override = default;

    void draw(bool isPicking) override;

	std::unique_ptr<Texture> armTexture_;
	std::unique_ptr<Texture> diffTexture_;
	std::unique_ptr<Texture> dispTexture_;
	std::unique_ptr<Texture> aoTexture_;
};

