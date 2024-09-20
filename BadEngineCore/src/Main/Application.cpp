#include <imgui.h>

#include "ui/Imgui/imgui_impl_glfw.h"
#include "ui/Imgui/imgui_impl_opengl3.h"
#include "Application.h"
#include "Diagnostics/Error.h"
#include "Timer/timer.h"
#include "ResourceLoader/ModelLoader.h"
#include "ECS/Behaviour/BehaviourObject.h"
#include "ResourceLoader/TextureManager.h"

namespace be {

	ApplicationContainer::ApplicationContainer() :
		keyboard{ Add<Keyboard>() },
		mouse{ Add<Mouse>() },
		main_platform_window{ Add<MainPlatformWindow>(1200, 800, "Very sick tissue maker", keyboard, mouse) },
		window{ Add<Window>() },
		renderer{ Add<Renderer>(main_platform_window.GetWidth(), main_platform_window.GetHeight()) },
		timer{ Add<Timer>() }
	{
	}

	Application::~Application()
	{
		m_imgui.Destroy();
		glfwTerminate();
	}

	void Application::EngineStart()
	{
		be::TextureManager::Init();
		m_imgui.Start(m_container.main_platform_window.GetGLFWWindow(), config_flag);
		m_container.renderer.Init();
		m_container.window.SetCurrentContext(m_container.main_platform_window.GetGLFWWindow());
		ErrorHandler::Handle();
		HandleErrorActions();
		Init();
	}

	void Application::EngineRun()
	{
		EngineStart();
		while (!m_container.main_platform_window.IsClosed() && m_running)
		{
			//frame start
			BehaviourManagerStore::GetBehaviourManager().CallAllUpdateFunctions();
			m_container.renderer.Render();
			m_imgui.Render(m_container.main_platform_window.GetGLFWWindow(), m_container.renderer, config_flag);

			//frame end
			m_container.main_platform_window.Update();
			m_container.timer.UpdateDeltaTime();
			glfwPollEvents();
		}
	}

	void Application::Init() {}

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
