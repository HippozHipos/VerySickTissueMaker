#pragma once

#include "renderer/camera/Camera.h"
#include "renderer/buffers/FrameBuffer.h"

namespace vstmr {

	class Window;
	class Viewport
	{
	public:
		Viewport(int x, int y, int width, int height, Window* window);

	public:
		void UpdateViewport();
		PerspectiveCamera& GetCamera();
		void ClearColor(float r, float g, float b, float a) const;
		FrameBuffer& GetFrameBuffer();

	public:
		int x = 0; int y = 0; int width = 0; int height = 0;

	private:
		FrameBuffer m_FrameBuffer;
		Window* m_window;
		PerspectiveCamera m_camera{ glm::radians(90.0f), 600.0f / 600.0f, 0.1f, 100.0f };
	};

}