#pragma once
#include "models/models.hh"
#include <vector>

//TODO: add documentation
class Scene 
{
public:
    void addModel(Model* model);
    void draw();

private:
    std::vector<Model*> models_;
};