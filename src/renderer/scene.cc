#include "scene.hh"
#include "camera/camera.hh"
#include <glm/glm.hpp>

Scene::Scene() : camera_(35.0f, 800.0f / 600.0f, 0.1f, 100.0f)
{}

void Scene::addModel(Model* model)
{
	this->models_.push_back(model);
}

void Scene::draw() 
{
	this->camera_.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	this->camera_.setPitch(-90.0f); 
	this->camera_.setYaw(-90.0f); 
	this->camera_.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));


	glm::mat4 view = this->camera_.getViewMatrix();
    glm::mat4 projection = camera_.getProjectionMatrix();


	for (Model* model : this->models_)
	{
		model->setProjectionMatrix(projection);
		model->setViewMatrix(view);
		model->draw();
	}
}
