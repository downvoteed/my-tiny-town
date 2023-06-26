#include "event-handler.hh"
#include "imgui/imgui.h"
#include <glfw/glfw3.h>

EventHandler::EventHandler(GLFWwindow* window, Camera& camera) : window_(window), camera_(camera) 
{
    // We are setting the user pointer to this class so
	//that we can access it in the  static callbacks
	glfwSetWindowUserPointer(window, this);
}

void EventHandler::registerCallbacks()
{
	glfwSetScrollCallback(this->window_, EventHandler::scrollCallback);
	glfwSetCursorPosCallback(this->window_, EventHandler::mouseCallback);
}

Camera& EventHandler::getCamera() const
{
	return this->camera_;
}

void EventHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!ImGui::GetIO().WantCaptureMouse && !ImGui::IsWindowHovered())

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
	
	if (!ImGui::GetIO().WantCaptureMouse && !ImGui::IsWindowHovered())
	{
		EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
		handler->getCamera().processMouseScroll(yoffset);
	}
}

