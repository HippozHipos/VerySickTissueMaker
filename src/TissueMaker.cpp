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
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_window.Update();
			glfwPollEvents();
		}
	}

}
