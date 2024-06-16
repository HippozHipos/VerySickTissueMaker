#pragma once

#include "Window/Window.h"

namespace vstm {

	class Application
	{
	public:
		Application();
		~Application() = default;

	public:
		void HanldeErrorActions();
		void Run();

	private:
		bool m_running = true;
		Window m_window;
	};

}
