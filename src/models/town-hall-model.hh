#pragma once
#include "models.hh"

class TownHall : public Model
{
public:
	TownHall(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation);
	~TownHall() = default;

	void draw(bool isPicking) const override;
};
