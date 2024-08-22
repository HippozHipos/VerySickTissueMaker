#pragma once

#include "Renderer/Renderer.h"

#include "Window/Window.h"

#include "renderer/Texture.h"

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

		//TextureManager m_texture_manager;
	};

}
