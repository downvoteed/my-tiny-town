#include "camera/camera.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspect, float near, float far)
        : position_(0.0f, 0.0f, 3.0f),
          front_(0.0f, 0.0f, -1.0f),
          up_(0.0f, 1.0f, 0.0f),
          fov_(fov),
          aspect_(aspect),
          near_(near),
          far_(far) {}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position_, position_ + front_, up_);
}

glm::mat4 Camera::getProjectionMatrix() const 
{
	return glm::perspective(glm::radians(fov_), aspect_, near_, far_);
}

void Camera::processMouseLeftClick(float xoffset, float yoffset)
{
	float sensitivity = 0.001f;  // Adjust as needed
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    position_.x += xoffset;
    position_.y += yoffset;

    yaw_ += xoffset;
    pitch_ += yoffset;

    updateCameraVectors();
}

void Camera::processMouseRightClick(float xoffset, float yoffset)
{
    //float sensitivity = 0.05f;  // Ajustez selon vos besoins
    //xoffset *= sensitivity;
    //yoffset *= sensitivity;

    //// Calculez la nouvelle position de la caméra
    //glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);  // Position du plan
    //glm::vec3 direction = position_ - target;
    //float radius = glm::length(direction);
    //float angle = atan2(direction.z, direction.x);
    //angle += glm::radians(xoffset);
    //float camX = target.x + radius * cos(angle);
    //float camZ = target.z + radius * sin(angle);
    //position_ = glm::vec3(camX, position_.y, camZ);

    //// Assurez-vous que la caméra est toujours orientée vers le plan
    //front_ = glm::normalize(target - position_);

    //updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
	if (fov_ >= 1.0f && fov_ <= 45.0f)
		fov_ -= yoffset;
	if (fov_ <= 1.0f)
		fov_ = 1.0f;
	if (fov_ >= 300.0f)
		fov_ = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_ = glm::normalize(front);
}

void Camera::setAspectRatio(const float aspect)
{
	this->aspect_ = aspect;
}

void Camera::setPosition(const glm::vec3& position)
{
	this->position_ = position;
	this->updateCameraVectors();
}

void Camera::setYaw(const float yaw)
{
	this->yaw_ = yaw;
	this->updateCameraVectors();
}

void Camera::setPitch(float pitch)
{
	this->pitch_ = pitch;
	this->updateCameraVectors();
}
