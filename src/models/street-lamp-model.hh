#pragma once
#include "models.hh"
#include <memory>

class StreetLamp : public Model
{
public:
	StreetLamp(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~StreetLamp() = default;

	void draw(bool isPicking) override;

private:
	std::unique_ptr<Texture> normal_;
	std::unique_ptr<Texture>  roughness_;
	std::unique_ptr<Texture>  metallic_;
};
