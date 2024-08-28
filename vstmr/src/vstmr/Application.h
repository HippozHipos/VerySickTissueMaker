#pragma once

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "renderer/Texture.h"
#include "timer/Timer.h"

struct ImGuiIO;

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
		virtual void Update(float deltaTime);
		virtual void ImGui(ImGuiIO& io);
		virtual void End();

	private:
		void ImGuiSetup();
		void ImGuiDraw();

	protected:
		bool m_running = true;

		Timer<float> m_timer{};

		Window m_window;
		Renderer m_renderer;

		TextureManager m_texture_manager;
	};

}
