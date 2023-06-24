#include <iostream>
#include "ui/application.hh"
#include "ui/imgui-layer.hh"
#include "ui/windows/demo-window.hh"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"

int main()
{
	Application* app = Application::instance();
	ImGuiLayer imgui = ImGuiLayer(app->getWindow());
	DemoWindow demo = DemoWindow();

	while (!app->shouldClose())
	{
		imgui.begin();
		demo.render();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	ImGui::Render();
	//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		imgui.end();
		app->pollEvents();
		app->swapBuffers();
	}
	glfwTerminate();
	return 0;
}