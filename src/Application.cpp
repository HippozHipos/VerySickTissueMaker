#include "Application.h"
#include "util/Logger.h"
#include "util/Error.h"

namespace vstm {

	Application::Application() :
		m_window{ 600, 600, "Very sick tissue maker", nullptr, nullptr }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");
	}

	void Application::Run()
	{
		ErrorHandler::Handle();
		HanldeErrorActions();
		while (!m_window.IsClosed() && m_running)
		{
			if (m_window.MouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
			{
				VSTM_CON_LOGINFO("Mouse pressed");
			}
			m_window.Fill(1, 0, 0, 1);
			m_window.Update();
			glfwPollEvents();
			ErrorHandler::Handle();
			HanldeErrorActions();
		}
	}

	void Application::HanldeErrorActions()
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
