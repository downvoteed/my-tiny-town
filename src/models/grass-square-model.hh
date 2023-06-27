#pragma once
#include "models.hh"

class GrassSquare : public Model
{
public:
	GrassSquare(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation);
	~GrassSquare() = default;

	void draw(bool isPicking) const override;
};
