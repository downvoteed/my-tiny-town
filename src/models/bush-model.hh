#pragma once
#include "models.hh"

class Bush : public Model
{
public:
	Bush(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~Bush() = default;

	void rotate(float angle, const glm::vec3& axis) override;

	void draw(bool isPicking) override;
};
