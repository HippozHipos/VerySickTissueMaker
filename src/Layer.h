#pragma once

namespace vstm {

	class Window;
	class Renderer;

	class Layer
	{
	public:
		Layer();
		virtual ~Layer() = default;

	public:
		virtual void Start();
		virtual void Update();
		virtual void End();

		void SetWindow(Window* win);
		void SetRenderer(Renderer* renderer);

	protected:
		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr;
	};

}