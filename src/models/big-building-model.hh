#pragma once
#include "models.hh"

class BigBuilding : public Model
{
public:
	BigBuilding(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~BigBuilding() = default;

	void rotate(float angle, const glm::vec3& axis) override;

	void draw(bool isPicking) override;
};
