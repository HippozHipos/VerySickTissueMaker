#include <imgui.h>
#include <ui/imgui/imgui_impl_glfw.h>
#include <ui/imgui/imgui_impl_opengl3.h>

#include "Application.h"
#include "diagnostics/Error.h"
#include "timer/timer.h"

#include "ECS/BehaviouralSceneObject.h"

namespace vstmr {

	//This just makes everything super convenient since it makes these things 
	//readily available within any scene object
	ApplicationContainer::ApplicationContainer() :
		keyboard{ Add<Keyboard>() },
		mouse{ Add<Mouse>() },
		window{ Add<Window>(600, 600, "Very sick tissue maker", keyboard, mouse) },
		renderer{ Add<Renderer>() },
		timer{ Add<Timer>() },

		camera{ Add<Camera>(glm::radians(90.0f), 1, 0.001, 10000) }//temporarily here
	{
	}

	Application::Application() 
	{
		m_imgui.Start(m_container.window.GetGLFWWindow());
		m_container.renderer.Init();
		ErrorHandler::Handle();
		HandleErrorActions();
	}

	Application::~Application()
	{
		m_imgui.Destroy();
		glfwTerminate();
	}

	void Application::Run()
	{
		BehaviourManagerStore::GetBehaviourManager().CallAllStartFunctions();
		while (!m_container.window.IsClosed() && m_running)
		{
			//frame start
			BehaviourManagerStore::GetBehaviourManager().CallAllUpdateFunctions();
			m_container.renderer.Render();
			m_imgui.Render(m_container.window.GetGLFWWindow());

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
