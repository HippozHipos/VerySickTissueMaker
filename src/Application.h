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
		int m_width, m_height, m_colorchannels;
		unsigned char* m_image;
		GLuint m_textureid;
		bool m_running = true;
		double m_lastX, m_lastY;
		bool m_firstMouse;
		Window m_window;
		Renderer m_renderer{};
	};

}
