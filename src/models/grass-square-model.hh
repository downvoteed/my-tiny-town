#pragma once
#include "models.hh"

class GrassSquare : public Model
{
public:
	GrassSquare(std::string name, const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation);
	~GrassSquare() = default;

	void draw(bool isPicking) override;
};
