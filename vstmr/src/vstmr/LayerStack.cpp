#include "Layer.h"
#include "diagnostics/Assert.h"
#include "LayerStack.h"
#include "renderer/Renderer.h"

namespace vstmr {

	void LayerStack::_Init(Window* window, Renderer* renderer)
	{
		m_window = window;
		m_renderer = renderer;
	}

	void LayerStack::_Start()
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->Start();
		}
	}

	void LayerStack::_Update(float deltaTime)
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->Update(deltaTime);
		}
	}

	void LayerStack::_End()
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->End();
		}
	}

	Layer* LayerStack::GetLayer(size_t i)
	{
		return m_layers[i];
	}

	void LayerStack::PushLayer(Layer* layer, size_t index, bool overlay)
	{
		layer->SetWindow(m_window);
		layer->SetRenderer(m_renderer);
		if (!overlay)
		{
			VSTM_ASSERT(index <= m_num_non_overlays,
				"Index out of range. Valid Range = 0 to {}", m_num_non_overlays);

			m_layers.emplace(m_layers.begin() + index, layer);
			m_num_non_overlays++;
		}
		else
		{
			VSTM_ASSERT(index <= m_num_overlays,
				"Index out of range. Valid Range = 0 to {}", m_num_overlays);

			m_layers.emplace(m_layers.begin() + m_num_non_overlays + index, layer);
			m_num_overlays++;
		}
	}

	void LayerStack::PushFrontLayer(Layer* layer, bool overlay)
	{
		layer->SetWindow(m_window);
		layer->SetRenderer(m_renderer);
 		if (!overlay)
		{
			m_layers.emplace(m_layers.begin(), layer);
			m_num_non_overlays++;
		}
		else
		{
			m_layers.emplace(m_layers.begin() + m_num_non_overlays, layer);
			m_num_overlays++;
		}
	}

	void LayerStack::PushBackLayer(Layer* layer, bool overlay)
	{
		layer->SetWindow(m_window);
		layer->SetRenderer(m_renderer);
		if (!overlay)
		{
			m_layers.emplace(m_layers.end() - m_num_overlays, layer);
			m_num_non_overlays++;
		}
		else
		{
			m_layers.emplace_back(layer);
			m_num_overlays++;
		}
	}

	size_t LayerStack::Size() const
	{
		return m_layers.size();
	}

}