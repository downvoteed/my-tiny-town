#include "demo-window.hh"
#include "imgui/imgui.h"

DemoWindow::DemoWindow(Scene& scene): Window(scene)
{
}

void DemoWindow::render()
{
	ImGui::ShowDemoWindow();
}
