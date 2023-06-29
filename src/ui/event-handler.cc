#include "event-handler.hh"
#include "imgui/imgui.h"

EventHandler::EventHandler(GLFWwindow* window, Camera& camera) : window_(window), camera_(camera) 
{
    // We are setting the user pointer to this class so
	//that we can access it in the  static callbacks
	glfwSetWindowUserPointer(window, this);
}

void EventHandler::registerCallbacks()
{
//	glfwSetScrollCallback(this->window_, EventHandler::scrollCallback);
//	glfwSetCursorPosCallback(this->window_, EventHandler::mouseCallback);
	glfwSetFramebufferSizeCallback(this->window_, EventHandler::framebuffer_size_callback);
	glfwSetWindowSizeCallback(this->window_, EventHandler::framebuffer_size_callback);
}

Camera& EventHandler::getCamera() const
{
	return this->camera_;
}

void EventHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!ImGui::GetIO().WantCaptureMouse)

	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			handler->getCamera().processMouseLeftClick(xpos, ypos);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			handler->getCamera().processMouseRightClick(xpos, ypos);
		}
	}
}

void EventHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
		handler->getCamera().processMouseScroll(yoffset);
	}
}

void EventHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(Application::instance()->getPannelLeftWidth(), 0, width - Application::instance()->getPannelLeftWidth(), height);
}
