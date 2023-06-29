#include <iostream>
#include "ui/application.hh"
#include "ui/imgui-layer.hh"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.hh"
#include "event-handler.hh"
#include "grass-plane-model.hh"
#include "town-hall-model.hh"
#include "grass-square-model.hh"

int main()
{
	Application* app = Application::instance();
	Scene scene = Scene();
	// define callbacks before intializing ImGui
	// https://stackoverflow.com/a/72509936
	EventHandler eventHandler = EventHandler(app->getWindow(), scene.getCamera());
	eventHandler.registerCallbacks();
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());

	GrassPlane grass("assets/textures/diff/grass.jpg", glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);

//	TownHall townHall("assets/textures/diff/Walls_Albedo.png", glm::vec3(0.0f, 0.0f, 0.0f),
//		glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	GrassSquare grassSquare("assets/textures/diff/grass-square-diffuse.jpg", glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);

	
	scene.addModel(grass.getID(), &grass);
	//scene.addModel(&townHall);
	scene.addModel(grassSquare.getID(), &grassSquare);


	while (!app->shouldClose())
	{
		app->pollEvents();
		imgui.begin();
		app->render();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.draw();
		imgui.end();
		app->swapBuffers();
	}

	glfwTerminate();
	return 0;
}