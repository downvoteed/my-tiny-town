#include "camera/camera.hh"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(float fov, float aspect, float near, float far)
        : position_(0.0f, 10.0f, 80.0f),
          front_(0.0f, 0.0f, -1.0f),
          up_(0.0f, 1.0f, 0.0f),
          right_(1.0f, 0.0f, 0.0f), 
          worldUp_(0.0f, 1.0f, 0.0f), 
          fov_(fov),
          aspect_(aspect),
          near_(near),
          far_(far) {
    updateCameraVectors();
}

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
    float sensitivity = 0.1f;
    yaw_ += xoffset * sensitivity;
    pitch_ -= yoffset * sensitivity;

    // Clamp the pitch to prevent the camera from flipping over
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    position_ += front_ * yoffset; // move forward or backwards
}


void Camera::updateCameraVectors()
{
    std::cout << "Yaw: " << yaw_<< ", Pitch: " << pitch_ << std::endl;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_    = glm::normalize(glm::cross(right_, front_));
}


void Camera::setAspectRatio(const float aspect)
{
	this->aspect_ = aspect;
}

void Camera::setPitch(float pitch)
{
	this->pitch_ = pitch;
	updateCameraVectors();
}

void Camera::setYaw(float yaw)
{
	this->yaw_ = yaw;
	updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& position)
{
    this->position_ = position;
}

glm::vec3 Camera::getPosition() const
{
	return this->position_;
}

glm::vec3 Camera::getFront() const
{
	return this->front_;
}

glm::vec3 Camera::getRight () const
{
	return this->right_;
}

float Camera::getPitch() const
{
	return this->pitch_;
}

float Camera::getYaw() const
{
	return yaw_;
}

void Camera::move(const glm::vec3& offset)
{
    position_ += offset;
}


