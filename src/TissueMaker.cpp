#include "TissueMaker.h"
#include "util/Logger.h"

namespace vstm {

	TissueMaker::TissueMaker() :
		m_window{ 600, 600, "Very sick tissue maker", nullptr, nullptr }
	{
		VSTM_TRACE_LOGINFO("TissueMaker constructed");
	}

	void TissueMaker::Run()
	{
		while (!m_window.IsClosed())
		{
			glfwPollEvents();
			if (m_window.KeyPressed(GLFW_KEY_Z))
			{
				VSTM_CON_LOGINFO("Pressed up");
			}
			m_window.Update();
		}
	
	}

}
