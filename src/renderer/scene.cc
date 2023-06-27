#include "scene.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "application.hh"
#include "utils/utils.hh"

Scene::Scene() : camera_(35.0f, 800.0f / 600.0f, 0.1f, 100.0f), frameBuffer_()
{
	this->camera_.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	this->camera_.setPitch(-90.0f); 
	this->camera_.setYaw(-90.0f); 
	this->camera_.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));

}

void Scene::addModel(Model* model)
{
	this->models_.push_back(model);
}

void Scene::draw() 
{


	// if left mouse button is pressed
	//fbo.bind();
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		if (glfwGetMouseButton(Application::instance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			FrameBuffer& fbo = this->getFrameBuffer();
			fbo.bind();
			unsigned char pixelColor[3]; 
			int mouseX = 0, mouseY = 0;
			glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);
			glm::vec3 color(pixelColor[0], pixelColor[1], pixelColor[2]);

			size_t objectID = colorToId(color);
			std::cout << "Object ID: " << objectID << std::endl;
			// TODO

			fbo.unbind();
		}
	}
	glm::mat4 view = this->camera_.getViewMatrix();
	glm::mat4 projection = camera_.getProjectionMatrix();


	for (Model* model : this->models_)
	{
		//std::cout << "Drawing model: " << model->getID() << std::endl;
		model->setProjectionMatrix(projection);
		model->setViewMatrix(view);
		model->draw();
	}
}

Camera& Scene::getCamera()
{
	return this->camera_;
}

FrameBuffer& Scene::getFrameBuffer()
{
	return this->frameBuffer_;
}
