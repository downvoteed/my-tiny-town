#include <iostream>
#include "ui/application.hh"
#include "ui/imgui-layer.hh"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.hh"
#include "event-handler.hh"
#include "grass-plane-model.hh"
#include "building-model.hh"
#include "grass-square-model.hh"
#include "road-square-model.hh"
#include "street-lamp-model.hh"
#include "company-model .hh"
#include "skybox.hh"
#include "house-model.hh"

int main()
{
	Application* app = Application::instance();
	Scene scene = Scene();
	// define callbacks before intializing ImGui
	// https://stackoverflow.com/a/72509936
	EventHandler eventHandler = EventHandler(app->getWindow(), scene.getCamera());
	eventHandler.registerCallbacks();
	glfwSetWindowUserPointer(app->getWindow(), &scene);
	glfwSetCursorPosCallback(app->getWindow(), cursor_position_callback);
    glfwSetScrollCallback(app->getWindow(), scroll_callback);
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());

	GrassPlane grass("Grass plane", glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(40.f, 40.f, 40.f), 90.0f);

	Building building("Building", "assets/models/b.obj", "assets/textures/diff/b.jpg", glm::vec3(-0.20, 0.0f, 3.0f),
		glm::vec3(0.002f, 0.002f, 0.002f), 0.0f);

	GrassSquare grassSquare("Grass block","assets/models/grass-square.obj" ,
		"assets/textures/diff/grass-square-diffuse.jpg", glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(0.01f, 0.01f, 0.01f), -90.0f);

	RoadSquare roadSquare("Road block", "assets/models/road.obj", "assets/textures/diff/road-texture.png",
		glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.3f, 0.5f, 0.5f), -90.0f);

	StreetLamp streetLamp("Street Lamp", "assets/models/Lamp.obj", "assets/textures/diff/street-lamp-diff.png",
		glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.1f, 0.1f, 0.1f), -90.0f);

	CompanyBuilding companyBuilding("Company building", "assets/models/company-building.obj", "assets/textures/diff/company-building-diff.jpg",
		glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.002f, 0.002f, 0.002f), 0.0f);


	House house("House", "assets/models/house.obj", "assets/textures/diff/house-diff.jpg",
		glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.03f, 0.03f, 0.03f), 0.0f);
	


	
	scene.addModel(grass.getID(), &grass);
	scene.addModel(building.getID(), &building);
	scene.addModel(grassSquare.getID(), &grassSquare);
	scene.addModel(roadSquare.getID(), &roadSquare);
	scene.addModel(streetLamp.getID(), &streetLamp);
	scene.addModel(companyBuilding.getID(), &companyBuilding);
	scene.addModel(house.getID(), &house);

	// init interface
	Application::instance()->init(scene);


	while (!app->shouldClose())
	{
		app->pollEvents();
		imgui.begin();
		app->render(scene);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		scene.draw();
		imgui.end();
		app->swapBuffers();
	}

	glfwTerminate();
	return 0;
}