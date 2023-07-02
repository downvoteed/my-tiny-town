#include "scene.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "application.hh"
#include "utils/utils.hh"

static bool mouseButtonPressed = false;

Scene::Scene() : camera_(35.0f, 1280.0f / 780.0f, 0.1f, 1000.0f), frameBuffer_()
{
	camera_.setYaw(-90.0f);
	camera_.setPitch(0.f); // Make the camera look straight ahead
}


void Scene::addModel(size_t id, Model* model)
{
	this->models_.insert({ id, model });
}

void Scene::draw()
{
	glm::mat4 view = this->camera_.getViewMatrix();
	glm::mat4 projection = camera_.getProjectionMatrix();

	bool mouseButtonCurrentlyPressed = glfwGetMouseButton(Application::instance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

	if (!ImGui::GetIO().WantCaptureMouse && mouseButtonCurrentlyPressed && !mouseButtonPressed)
	{
		FrameBuffer& fbo = this->getFrameBuffer();
		fbo.bind();

		for (const auto& [_, model] : this->models_)
		{
			model->setProjectionMatrix(projection);
			model->setViewMatrix(view);
			model->draw(true);

		}

		unsigned char pixelColor[3];
		double mouseX, mouseY;

		glfwGetCursorPos(Application::instance()->getWindow(), &mouseX, &mouseY);

		int currentWidth, currentHeight;
		glfwGetFramebufferSize(Application::instance()->getWindow(), &currentWidth, &currentHeight);

		glViewport(Application::instance()->getPannelLeftWidth(), 0, currentWidth - Application::instance()->getPannelLeftWidth(), currentHeight);

		int textureX = static_cast<int>(mouseX);
		int textureY = static_cast<int>((currentHeight - mouseY));

		std::cout << textureX << " " << textureY << std::endl;

		glReadPixels(textureX, textureY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);

		glm::vec3 color = glm::vec3(pixelColor[0], pixelColor[1], pixelColor[2]);
		std::cout << "Color: " << color.x << " " << color.y << " " << color.z << std::endl;

		size_t objectID = colorToId(color);
		std::cout << "Object ID: " << objectID << std::endl;

		for (const auto& [_, tempModel] : this->models_)
		{
			tempModel->setSelected(false);
			if (models_.find(objectID) != models_.end())
				this->setSelectedModel(objectID);
		}
		if (models_.find(objectID) != models_.end())
		{
			auto model = this->models_.at(objectID);
			bool isAlreadySelected = model->isSelected();

			if (!isAlreadySelected && objectID != 1)
				model->setSelected(true);
		}
		else
		{
			this->setSelectedModel(0);
		}
		if (objectID == 1)
			this->setSelectedModel(0);

		fbo.unbind();
	}


	for (const auto& [_, model] : this->models_)
	{
		model->setProjectionMatrix(projection);
		model->setViewMatrix(view);
		if (model->isSelected())
		{
			model->drawStencil();
			model->draw(false);
			model->drawOutline();
		}
		else
			model->draw(false);
	}
	mouseButtonPressed = mouseButtonCurrentlyPressed;
}

Camera& Scene::getCamera()
{
	return this->camera_;
}

FrameBuffer& Scene::getFrameBuffer()
{
	return this->frameBuffer_;
}

void Scene::setSelectedModel(const size_t id)
{
	if (id == 0)
		this->selectedModel_ = nullptr;
	else
		this->selectedModel_ = this->models_.at(id);
}

Model* Scene::getSelectedModel()
{
	return this->selectedModel_;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Get the user pointer and assume it is a Scene instance
	Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));

	// Call the member function
	scene->processScroll(xoffset, yoffset);
}



void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	static Model* lastSelectedModel = nullptr;
	static double lastX = xpos;
	static double lastY = ypos;

	Scene* scene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
	Model* selectedModel = scene->getSelectedModel();

	float dx = xpos - lastX;
	float dy = ypos - lastY;

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (!ImGui::GetIO().WantCaptureMouse && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (selectedModel != lastSelectedModel)
		{
			lastSelectedModel = selectedModel;
		}

		glm::vec3 forward = scene->getCamera().getFront();
		glm::vec3 right = scene->getCamera().getRight();


		if (selectedModel == nullptr)
		{
			// Sensitivity factor for the mouse movement
			float sensitivity = 0.04f;

			// Movement along camera's own axes
			scene->getCamera().move(-dx * sensitivity * right + dy * sensitivity * forward);

			return;
		}

		glm::vec3 offset = dx * 0.06f * right - dy * 0.4f * forward;
		selectedModel->setPosition(selectedModel->getPosition() + offset);
	}
	else if (!ImGui::GetIO().WantCaptureMouse && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		float yaw = scene->getCamera().getYaw();
		float pitch = scene->getCamera().getPitch();

		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		scene->getCamera().setYaw(yaw);
		scene->getCamera().setPitch(pitch);

	}
	else
	{
		lastSelectedModel = nullptr;
	}
}




void Scene::processScroll(double xoffset, double yoffset)
{
	// handle scroll event...
	camera_.processMouseScroll(yoffset);
}

std::map<size_t, Model*>& Scene::getModels() 
{
	return this->models_;
}
