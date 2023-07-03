#pragma once
#include "models.hh"

class OfficeBuilding : public Model
{
public:
	OfficeBuilding(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~OfficeBuilding() = default;

	void rotate(float angle, const glm::vec3& axis) override;

	void draw(bool isPicking) override;
};
