#pragma once

#include <vector>
#include <memory>

#include "renderer/camera/Camera.h"

namespace vstmr {

	class Window;
	class Renderer;
	class Viewport;

	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

	public:
		virtual void Start();
		virtual void Update(float deltaTime);
		virtual void End();

		void SetWindow(Window* win);
		void SetRenderer(Renderer* renderer);

		size_t NumViewports(size_t i) const;
		std::shared_ptr<Viewport> AddViewport(int x, int y, int width, int height);
		Viewport* GetViewport(size_t i);

		PerspectiveCamera& GetCamera();

	protected:
		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr; //debateable if Layer should have renderer.
		std::vector<std::shared_ptr<Viewport>> m_viewports;
		PerspectiveCamera m_camera{ glm::radians(90.0f), 600.0f / 600.0f, 0.1f, 100.0f };
	};

}