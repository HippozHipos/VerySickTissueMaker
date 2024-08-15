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
		bool m_running = true;
		void ProcessInput(double deltaTime);
		void CaptureMouse(GLFWwindow* window);
		double m_lastX, m_lastY;
		bool m_firstMouse;
		Window m_window;
		Renderer m_renderer{};
	};

}
