#pragma once

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "renderer/Texture.h"
#include "timer/Timer.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"

struct ImGuiIO;

namespace vstmr {

	//This just makes everything super convenient since it makes these things 
	//readily available within any scene object
	struct ApplicationContainer : public SceneContainer
	{
		ApplicationContainer();
		Keyboard& keyboard;
		Mouse& mouse;
		Window& window;
		Renderer& renderer;
	};

	class Application
	{
	public:
		Application();
		virtual ~Application();

	public:
		void HandleErrorActions();
		void Run();

	private:
		void ImGuiSetup();
		void ImGuiDraw();

	private:
		ApplicationContainer m_container;

		//probably should add some of the bellow as components as needed
		bool m_running = true;
		Timer<float> m_timer{};
		TextureManager m_texture_manager;
	};

}
