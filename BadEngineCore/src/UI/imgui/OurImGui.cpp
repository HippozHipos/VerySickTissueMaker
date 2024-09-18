#include "OurImGui.h"
#include "UI/Imgui/ImGuiDarkTheme.h"
#include "ECS/Behaviour/BehaviourObject.h"

#include "Renderer/Graphics.h"
#include "Main/Application.h"

namespace be {

	void OurImGui::Start(GLFWwindow* window, int config_flag)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      

		if (config_flag & Application::ENABLE_VIEWPORTS)
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    
		if (config_flag & Application::SETUP_MAIN_WINDOW_AS_DOCKSPACE)
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         

		ApplyImGuiDarkTheme();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.1f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(window, true);

		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void OurImGui::Render(GLFWwindow* window, Renderer& renderer, int config_flag)
	{	
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (config_flag & Application::SETUP_MAIN_WINDOW_AS_DOCKSPACE)
			ImGui::DockSpaceOverViewport(ImGui::GetID("Main dockspace"), ImGui::GetMainViewport());

		BehaviourManagerStore::GetBehaviourManager().CallAllUIFunctions();
		renderer.RenderImGuiViewport();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}
	}

	void OurImGui::Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}