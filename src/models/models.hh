#pragma once
#include <glm/glm.hpp>
#include <string>
#include "textures/textures.hh"

/**
 * @brief Interface for all models.
 */
class Model 
{
public:
    /**
     * @brief Construct a new Model object. 	
	 * @param texturePath 
	 * @param position 
	 * @param size 
	 * @param rotation 
	 .
     */
    Model(const std::string& texturePath, const glm::vec3& position, const glm::vec3& size, float rotation) : 
        texture_(texturePath), position_(position), size_(size), rotation_(rotation) {}
    virtual ~Model() = default;

    /**
     * @brief set the position of the model.
     */
	virtual void setPosition(const glm::vec3& position) = 0;
    /**
	 * @brief set the size of the model.
	 */
	virtual void setSize(const glm::vec3& size) = 0;
    /**
     * @brief set the rotation of the model.
     */
	virtual void setRotation(float rotation) = 0;
    /**
     * @brief get the position of the model.
     */
    virtual glm::vec3 getPosition() const = 0;
    /**
	 * @brief get the size of the model.
	 */
    virtual glm::vec3 getSize() const = 0;
    /**
	 * @brief get the rotation of the model.
	 */
    virtual float getRotation() const = 0;
    /**
	 * @brief draw the model.
	 */
    virtual void draw() const = 0;

private:
    Texture texture_;
    glm::vec3 position_;
    glm::vec3 size_;
    float rotation_;
};

