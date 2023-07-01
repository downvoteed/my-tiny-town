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
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());

	GrassPlane grass("Grass plane", glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(40.f, 40.f, 40.f), 0.0f);

	Building townHall("Town Hall", "assets/models/b.obj", "assets/textures/diff/b.jpg", glm::vec3(-0.20, -8.0f, 3.0f),
		glm::vec3(0.002f, 0.002f, 0.002f), 0.0f);

	GrassSquare grassSquare("Grass block","assets/models/grass-square.obj" ,
		"assets/textures/diff/grass-square-diffuse.jpg", glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(0.01f, 0.01f, 0.01f), 0.0f);

	RoadSquare roadSquare("Road block", "assets/models/road.obj", "assets/textures/diff/road-texture.png",
		glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.3f, 0.5f, 0.5f), 0.0f);

	
	scene.addModel(grass.getID(), &grass);
	scene.addModel(townHall.getID(), & townHall);
	scene.addModel(grassSquare.getID(), &grassSquare);
	scene.addModel(roadSquare.getID(), &roadSquare);

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