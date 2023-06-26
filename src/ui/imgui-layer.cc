#include "imgui-layer.hh"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"

/**
 * @brief Construct a new ImGui Layer object
 * @param window The GLFW window
 */
ImGuiLayer::ImGuiLayer(GLFWwindow* window)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// [0] body text
	io.Fonts->AddFontFromFileTTF("assets/fonts/ContrailOne-Regular.ttf", 18);
	// H1 title
	// [1]
	io.Fonts->AddFontFromFileTTF("assets/fonts/ContrailOne-Regular.ttf", 45);
	// H2 title
	// [2]
	io.Fonts->AddFontFromFileTTF("assets/fonts/ContrailOne-Regular.ttf", 35);
	// H3 title
	// [3]
	io.Fonts->AddFontFromFileTTF("assets/fonts/ContrailOne-Regular.ttf", 25);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

/**
 * @brief Destroy the ImGui Layer object. Cleanup
 */
ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/**
 * @brief Begin a new ImGui frame
 */
void ImGuiLayer::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

/**
 * @brief End the ImGui frame
 */
void ImGuiLayer::end()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
