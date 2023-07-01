#pragma once
#include "models.hh"

class Building : public Model
{
public:
	Building(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~Building() = default;

	void draw(bool isPicking) override;
};
