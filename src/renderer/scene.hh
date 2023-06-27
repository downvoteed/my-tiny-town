#pragma once
#include "models/models.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <map>

//TODO: add documentation
class Scene 
{
public:
    Scene();
    /**
    * @brief Add a Moddel to the scene
    * @param model the model to add
    */
    void addModel(size_t id, Model* model);
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

private:
    std::map<size_t, Model*> models_;
    Camera camera_;
    FrameBuffer frameBuffer_;
};