#pragma once

#include "renderer/camera/Camera.h"

namespace vstmr {


	class Window;
	class Viewport
	{
	public:
		Viewport(int x, int y, int width, int height, Window* window);

	public:
		void UpdateViewport();
		PerspectiveCamera& GetCamera();

		//NOTE: REMOVE LATER
		float r = 1.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

	private:
		int m_x = 0;
		int m_y = 0;
		int m_width = 0;
		int m_height = 0;

		Window* m_window;
		PerspectiveCamera m_camera{ glm::radians(90.0f), 600.0f / 600.0f, 0.1f, 100.0f };
	};

}