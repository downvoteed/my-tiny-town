#include "scene.hh"
#include "camera/camera.hh"
#include "frame-buffer.hh"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "application.hh"
#include "utils/utils.hh"

Scene::Scene() : camera_(35.0f, 800.0f / 600.0f, 0.1f, 100.0f), frameBuffer_()
{
	this->camera_.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	this->camera_.setPitch(-90.0f); 
	this->camera_.setYaw(-90.0f); 
	this->camera_.setPosition(glm::vec3(0.0f, 20.0f, 0.0f));

}

void Scene::addModel(size_t id, Model* model)
{
    this->models_.insert({id, model});
}

void Scene::draw() 
{
    glm::mat4 view = this->camera_.getViewMatrix();
    glm::mat4 projection = camera_.getProjectionMatrix();

    if (!ImGui::GetIO().WantCaptureMouse && glfwGetMouseButton(Application::instance()->getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        FrameBuffer& fbo = this->getFrameBuffer();
        fbo.bind();

        for (const auto& [_, model] : this->models_)
        {
            model->setProjectionMatrix(projection);
            model->setViewMatrix(view);
            model->draw(true);
        }

        unsigned char pixelColor[3];
        double mouseX, mouseY;

        glfwGetCursorPos(Application::instance()->getWindow(), &mouseX, &mouseY);

        unsigned int viewport[4];
        glGetIntegerv(GL_VIEWPORT, (int*)viewport);

        // Convert cursor coordinates to texture coordinates
        int textureX = static_cast<int>(mouseX);
        int textureY = static_cast<int>(viewport[3] - mouseY);

        std::cout << textureX << " " << textureY << std::endl;

        glReadPixels(textureX, textureY, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixelColor);

        glm::vec3 color = glm::vec3(pixelColor[0], pixelColor[1], pixelColor[2]);
        std::cout << "Color: " << color.x << " " << color.y << " " << color.z << std::endl;

        size_t objectID = colorToId(color);
        std::cout << "Object ID: " << objectID << std::endl;

        this->models_.at(objectID)->setSelected(true);

        fbo.unbind();
    }

    for (const auto& [_, model] : this->models_)
    {
        model->setProjectionMatrix(projection);
        model->setViewMatrix(view);
        model->draw(false);
    }
}

Camera& Scene::getCamera()
{
	return this->camera_;
}

FrameBuffer& Scene::getFrameBuffer()
{
	return this->frameBuffer_;
}
