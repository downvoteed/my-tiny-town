#pragma once
#include "models/models.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <map>
#include <GLFW/glfw3.h>
#include "skybox.hh"

//TODO: add documentation
class Scene 
{
public:
    Scene();
    Scene (const Scene&) = default;
    /**
    * @brief Add a Moddel to the scene
    * @param model the model to add
    */
    void addModel(size_t id, Model* model);
    /**
     * @brief Remove a model from the scene
     */
    void removeModel(size_t id);
    /**
    * @brief Draw all the models in the scene
	*/
    void draw();

    /**
     * @brief Get the Camera object
     */
    Camera& getCamera();

    /**
	 * @brief Get the Frame Buffer object
	 */
    FrameBuffer& getFrameBuffer();

    /**
     * @brief Set the selected model
     */
    void setSelectedModel(size_t id);

    /**
     * @brief Get the selected model
	 */
    Model* getSelectedModel();

    void processScroll(double xoffset, double yoffset);

    std::map<size_t, Model*>& getModels();


private:
    std::map<size_t, Model*> models_;
    Model *selectedModel_ = nullptr;
    Camera camera_;
    FrameBuffer frameBuffer_;
    std::unique_ptr<SkyboxSunset> skybox_;

};

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
