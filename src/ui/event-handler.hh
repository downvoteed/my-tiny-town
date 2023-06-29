#pragma once
#include "camera/camera.hh"
#include "application.hh"


/**
 * @brief EventHandler class is responsible for handling user input.
 */
class EventHandler
{
public:
    EventHandler(GLFWwindow* window, Camera& camera);

    /**
     *  @brief Registers callbacks for user input.
     */
    void registerCallbacks();
    /**
     * @brief Right and left mouse click callback.
     * @param window window object.
     * @param xpos x position.
     * @param ypos y position.
     */
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    /**
     * @brief mouse scroll callback for zooming in and out.
     * @param window window object.
     * @param xoffset x offset.
     * @param yoffset y offset.
     */
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    /**
     *  @brief gets the camera object.
     */
    Camera& getCamera() const;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    Camera& camera_;
    GLFWwindow* window_;
};
