#include <imgui.h>

#include "ui/Imgui/imgui_impl_glfw.h"
#include "ui/Imgui/imgui_impl_opengl3.h"
#include "Application.h"
#include "Diagnostics/Error.h"
#include "Timer/timer.h"
#include "ResourceLoader/ModelLoader.h"
#include "ECS/BehaviouralSceneObject.h"

namespace be {

	//This just makes everything super convenient since it makes these things 
	//readily available within any scene object
	ApplicationContainer::ApplicationContainer() :
		keyboard{ Add<Keyboard>() },
		mouse{ Add<Mouse>() },
		window{ Add<Window>(600, 600, "Very sick tissue maker", keyboard, mouse) },
		renderer{ Add<Renderer>(window.GetWidth(), window.GetHeight()) },
		timer{ Add<Timer>() }
	{
	}

	Application::~Application()
	{
		m_imgui.Destroy();
		glfwTerminate();
	}

	void Application::Start()
	{
		m_imgui.Start(m_container.window.GetGLFWWindow(), config_flag);
		m_container.renderer.Init();
		ErrorHandler::Handle();
		HandleErrorActions();
		BehaviourManagerStore::GetBehaviourManager().CallAllStartFunctions();
	}

	void Application::Run()
	{
		Start();
		while (!m_container.window.IsClosed() && m_running)
		{
			//frame start
			BehaviourManagerStore::GetBehaviourManager().CallAllUpdateFunctions();
			m_container.renderer.Render();
			m_imgui.Render(m_container.window.GetGLFWWindow(), m_container.renderer, config_flag);

			//frame end
			m_container.window.Update();
			m_container.timer.UpdateDeltaTime();
			glfwPollEvents();
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
