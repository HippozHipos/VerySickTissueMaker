#pragma once
#include "pch.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Window/MainPlatformWindow.h"
#include "Renderer/Texture.h"
#include "Timer/Timer.h"

#include "Input/Keyboard.h" 
#include "Input/Mouse.h"

#include "UI/Imgui/BEImGui.h"

namespace be {

	/*!
	 * 
	 */
	struct ApplicationContainer : public SceneContainer
	{
		ApplicationContainer();
		Keyboard& keyboard;
		Mouse& mouse;
		MainPlatformWindow& main_platform_window;
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
		void EngineStart();
		void EngineRun();

		//intended to be used by user application in case anything that depends on the engine to be 
		//initialized first, needs to be initialized (example: imgui fonts)
		virtual void Init();

	public:
		static constexpr int SETUP_MAIN_WINDOW_AS_DOCKSPACE = 1 << 0;
		static constexpr int ENABLE_VIEWPORTS = 1 << 1;

	protected:
		int config_flag = 0;

	private:
		ApplicationContainer m_container;
		BEImGui m_imgui{};
		bool m_running = true;
	};

}
