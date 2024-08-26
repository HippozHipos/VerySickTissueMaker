#include "Layer.h"
#include "diagnostics/Assert.h"
#include "LayerStack.h"
#include "renderer/Renderer.h"

namespace vstmr {

	LayerStack::LayerStack(Window* window) :
		m_window{ window }
	{
	}

	void LayerStack::_Start(Renderer* renderer)
	{
		this->m_renderer = renderer;
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->Start();
		}
	}

	void LayerStack::_Update()
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->Update();
		}
	}

	void LayerStack::_End()
	{
		for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it)
		{
			(*it)->End();
		}
	}

	void LayerStack::PushLayer(Layer* layer, int index, bool overlay)
	{
		layer->SetWindow(m_window);
		layer->SetRenderer(m_renderer);
		if (!overlay)
		{
			/*VSTM_ASSERT(index <= m_num_non_overlays,
				"Index out of range. Valid Range = 0 to {}", m_num_non_overlays);*/

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

}