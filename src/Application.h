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
		Window m_window;
		vstm::Renderer m_renderer{};
	};

}
