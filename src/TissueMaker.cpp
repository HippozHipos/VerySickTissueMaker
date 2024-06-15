#include <cstdio>
#include <iostream>

#include "TissueMaker.h"
#include "util/Logger.h"

namespace vstm {

	TissueMaker::TissueMaker() :
		m_window{ 600, 600, "Very sick tissue maker", nullptr, nullptr }
	{

	}

	void TissueMaker::Run()
	{

		while (!m_window.IsClosed())
		{
			glfwPollEvents();
		}
	
	}

}
