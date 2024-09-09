#pragma once

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "renderer/Texture.h"
#include "timer/Timer.h"

#include "input/Keyboard.h" 
#include "input/Mouse.h"

struct ImGuiIO;

namespace vstmr {

	struct ApplicationContainer : public SceneContainer
	{
		ApplicationContainer();
		Keyboard& keyboard;
		Mouse& mouse;
		Window& window;
		Renderer& renderer;
		Timer& timer;

		//just here for now since camera systme isnt implemented
		vstmr::Camera& camera;
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
		bool m_running = true;
	};

}
