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
    * @brief set camera position
    */
    void setPosition(const glm::vec3& position);
    /**
    * @brief set camera pitch. Vertical angle.
	*/
    void setPitch(float pitch);
	/**
    * @brief set camera yaw. Horizontal angle.
    */  
    void setYaw(const float yaw);

private:
    void updateCameraVectors();

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    float fov_;
    float aspect_;
    float near_;
    float far_;
    float yaw_ = -90.0f;
    float pitch_ = 0.0f;
};
