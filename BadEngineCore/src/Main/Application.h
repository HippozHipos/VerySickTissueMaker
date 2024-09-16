#pragma once
#include "pch.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Renderer/Texture.h"
#include "Timer/Timer.h"

#include "Input/Keyboard.h" 
#include "Input/Mouse.h"

#include "UI/Imgui/OurImGui.h"

namespace be {

	struct ApplicationContainer : public SceneContainer
	{
		ApplicationContainer();
		Keyboard& keyboard;
		Mouse& mouse;
		Window& window;
		Renderer& renderer;
		Timer& timer;
	};

	class Application
	{
	public:
		Application() = default;
		virtual ~Application();

	public:
		void HandleErrorActions();
		void Start();
		void Run();

	public:
		static constexpr int SETUP_MAIN_WINDOW_AS_DOCKSPACE = 1 << 0;
		static constexpr int ENABLE_VIEWPORTS = 1 << 1;

	protected:
		int config_flag = 0;

	private:
		ApplicationContainer m_container;
		OurImGui m_imgui{};
		bool m_running = true;
	};

}