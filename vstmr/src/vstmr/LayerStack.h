#pragma once

#include <vector>
#include <memory>

namespace vstmr {

	class Renderer;
	class Window;
	class Layer;

	class LayerStack
	{
	public:
		LayerStack() = default;

	public:
		void PushLayer(Layer* layer, size_t index, bool overlay = false);
		void PushFrontLayer(Layer* layer, bool overlay = false);
		void PushBackLayer(Layer* layer, bool overlay = false);
		Layer* GetLayer(size_t i);
		size_t Size() const;

	public:
		//you can look but cannot touch
		void _Init(Window* window, Renderer* renderer);
		void _Start();
		void _Update(float deltaTime);
		void _End();

	private:
		std::vector<Layer*> m_layers;
		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr;
		int m_num_overlays = 0; //number of overlay layers
		int m_num_non_overlays = 0; //number of non-overlay layers
	};

}