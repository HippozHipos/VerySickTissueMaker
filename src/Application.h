#pragma once

#include "Renderer/Renderer.h"

#include "Window/Window.h"

namespace vstm {

	class Application
	{
	public:
		Application();
		~Application() = default;

	public:
		void HandleErrorActions();
		void Run();

	private:
		void ProcessInput(double deltaTime);

	private:
		bool m_running = true;
		double m_lastX, m_lastY;
		Window m_window;
		Renderer m_renderer{};
	};

}
