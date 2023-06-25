#pragma once
#include <glfw/glfw3.h>
#include "camera/camera.hh"

class EventHandler
{
public:
    EventHandler(GLFWwindow* window, Camera& camera);

    void registerCallbacks();
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    Camera& getCamera() const;

private:
    Camera& camera_;
    GLFWwindow* window_;
};
