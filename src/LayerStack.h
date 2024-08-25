#pragma once

#include <vector>
#include <memory>

namespace vstm {

	class Renderer;
	class Window;
	class Layer;

	class LayerStack
	{
	public:
		LayerStack(Window* window);

	public:
		void PushLayer(Layer* layer, int index, bool overlay = false);
		void PushFrontLayer(Layer* layer, bool overlay = false);
		void PushBackLayer(Layer* layer, bool overlay = false);

	public:
		//you can look but cannot touch
		void _Start(Renderer* renderer);
		void _Update();
		void _End();

	private:
		std::vector<Layer*> m_layers;
		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr;
		int m_num_overlays = 0; //number of overlay layers
		int m_num_non_overlays = 0; //number of non-overlay layers
	};

}