#pragma once
#include "models.hh"

class Cottage : public Model
{
public:
	Cottage(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~Cottage() = default;

	void rotate(float angle, const glm::vec3& axis) override;

	void draw(bool isPicking) override;
};
