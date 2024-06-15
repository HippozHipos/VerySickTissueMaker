#pragma once

#include "Window/Window.h"

namespace vstm {

	class TissueMaker
	{
	public:
		TissueMaker();
		~TissueMaker() = default;

	public:
		void Run();

	private:
		Window m_window;
	};

}
