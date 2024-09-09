#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "Application.h"
#include "diagnostics/Logger.h"
#include "diagnostics/Error.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"
#include "diagnostics/OpenglError.h"
#include "timer/timer.h"
#include "ui/imgui/ImGuiDarkTheme.h"

#include "ECS/BehaviouralSceneObject.h"

#include "renderer/BufferSetStore.h"
#include "ResourceLoader/MeshLoader.h"

namespace vstmr {

	//This just makes everything super convenient since it makes these things 
	//readily available within any scene object
	ApplicationContainer::ApplicationContainer() :
		keyboard{ Add<Keyboard>() },
		mouse{ Add<Mouse>() },
		window{ Add<Window>(600, 600, "Very sick tissue maker", keyboard, mouse) },
		renderer{ Add<Renderer>() },
		timer{ Add<Timer>() },
		camera{ Add<Camera>(glm::radians(90.0f), 1, 0.001, 1000) }
	{
	}

	Application::Application() 
	{
		m_container.renderer.Init();
	}

	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void Application::Run()
	{
		ImGuiSetup();

		ErrorHandler::Handle();
		HandleErrorActions();

		BehaviourManagerStore::GetBehaviourManager().CallAllStartFunctions();

		while (!m_container.window.IsClosed())// && m_running)
		{
			BehaviourManagerStore::GetBehaviourManager().CallAllUpdateFunctions();

			m_container.renderer.Render();
			ImGuiDraw();

			m_container.window.Update();
			m_container.timer.UpdateDeltaTime();
			glfwPollEvents();
			ErrorHandler::Handle();
			HandleErrorActions();
		}
	}

	void Application::ImGuiSetup()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		ApplyImGuiDarkTheme();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(m_container.window.GetGLFWWindow(), true);

		const char* glsl_version = "#version 130";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void Application::ImGuiDraw()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		BehaviourManagerStore::GetBehaviourManager().CallAllUIFunctions();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(m_container.window.GetGLFWWindow());
		}
	}

	void Application::HandleErrorActions()
	{
		for (size_t i = 0; i < ErrorHandler::NumActions(); i++)
		{
			switch (ErrorHandler::GetAction(i))
			{
				case ErrorHandler::TerminateApplication: m_running = false;

			}
		}
	}

}
