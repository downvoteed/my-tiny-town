#pragma once
#include <glm/glm.hpp>

/**
 * @brief Camera class
 */
class Camera 
{
public:
    /**
     * @brief Construct a new Camera object
     */
    Camera(float fov, float aspect, float near, float far);
    /**
     * @brief returns the view matrix calculated using the LookAt Matrix
     */
    glm::mat4 getViewMatrix() const;
    /**
	 * @brief returns the projection matrix
	 */
    glm::mat4 getProjectionMatrix() const;
    void processMouseLeftClick(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    /**
    * @brief set aspect ratio
	*/
    void setAspectRatio(const float aspect);
    /**
     * @brief set camera pitch angle
     */
    void setPitch(float pitch);
    /**
	 * @brief set camera yaw angle
	 */
    void setYaw(float yaw);
    /**
    * @brief set camera position
    */
    void setPosition(const glm::vec3& position);
    /**
     *  @brief get camera position
     */
    glm::vec3 getPosition() const;
    /**
	 * @brief get camera front vector
	 */
    glm::vec3 getFront() const;

    float getYaw() const;
    float getPitch() const;
    glm::vec3 getRight() const;

    void rotate(float dx, float dy);

	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 pivotPoint = glm::vec3(0.0f, 0.0f, 0.0f);

    void move(const glm::vec3& offset);

private:
    void updateCameraVectors();

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_ = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction_ = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 viewMatrix;
    float fov_;
    float aspect_;
    float near_;
    float far_;
    float yaw_ = -90.0f;
    float pitch_ = 0.0f;
};