#pragma once
#include "models.hh"

class Skyscraper : public Model
{
public:
	Skyscraper(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~Skyscraper() = default;

	void rotate(float angle, const glm::vec3& axis) override;

	void draw(bool isPicking) override;
};
