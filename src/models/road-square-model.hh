#pragma once
#include "models.hh"

class RoadSquare : public Model
{
public:
	RoadSquare(std::string name, const std::string& modelPath, const std::string& texturePath,
		const glm::vec3& position, const glm::vec3& size, float rotation);
	~RoadSquare() = default;

	void draw(bool isPicking) override;
};
