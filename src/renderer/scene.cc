#include "scene.hh"

void Scene::addModel(Model* model)
{
	this->models_.push_back(model);
}

void Scene::draw() 
{
	for (Model* model : this->models_)
	{
		model->draw();
	}
}
