#pragma once
#include "models/models.hh"
#include <vector>

//TODO: add documentation
class Scene 
{
public:
    /**
    * @brief Add a Moddel to the scene
    * @param model the model to add
    */
    void addModel(Model* model);
    /**
    * @brief Draw all the models in the scene
	*/
    void draw();

private:
    std::vector<Model*> models_;
};