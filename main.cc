#include <iostream>
#include "ui/application.hh"
#include "ui/imgui-layer.hh"
#include "ui/windows/demo-window.hh"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.hh"
#include "event-handler.hh"
#include "grass-plane-model.hh"

int main()
{
	Application* app = Application::instance();
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());
	DemoWindow demo = DemoWindow();

	Scene scene = Scene();
	EventHandler eventHandler = EventHandler(app->getWindow(), scene.getCamera());
	eventHandler.registerCallbacks();
	GrassPlane grass("assets/textures/diff/grass.jpg", glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	scene.addModel(&grass);


	while (!app->shouldClose())
	{
		glEnable(GL_DEPTH_TEST);
		imgui.begin();
		demo.render();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.draw();
		imgui.end();
		app->pollEvents();
		app->swapBuffers();
	}
	glfwTerminate();
	return 0;
}