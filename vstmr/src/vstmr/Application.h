#pragma once

#include "Renderer/Renderer.h"

#include "Window/Window.h"

#include "renderer/Texture.h"

namespace vstmr {

	class Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		void HandleErrorActions();
		void Run();

	public:
		//client
		virtual void Start();
		virtual void Update();
		virtual void End();

	private:
		//ours
		void _Start();
		void _Update();
		void _End();

	private:
		void ProcessInput(double deltaTime);

	protected:
		bool m_running = true;
		double m_lastX, m_lastY;
		Window m_window;
		Renderer m_renderer{};

		TextureManager m_texture_manager;
	};

}
