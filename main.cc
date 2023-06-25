#include <iostream>
#include "ui/application.hh"
#include "ui/imgui-layer.hh"
#include "ui/windows/demo-window.hh"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.hh"
#include "grass-plane-model.hh"

int main()
{
	Application* app = Application::instance();
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());
	DemoWindow demo = DemoWindow();

	Scene scene = Scene();
	GrassPlane grass("assets/textures/diff/grass.jpg", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	scene.addModel(&grass);


	while (!app->shouldClose())
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		imgui.begin();
		demo.render();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		scene.draw();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		imgui.end();
		app->pollEvents();
		app->swapBuffers();
	}
	glfwTerminate();
	return 0;
}