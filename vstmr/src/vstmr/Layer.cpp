#include "Layer.h"

namespace vstmr {

	void Layer::Start() 
	{
	}

	void Layer::Update()
	{
	}

	void Layer::End()
	{
	}

	void Layer::SetWindow(Window* win)
	{
		m_window = win;
	}

	void Layer::SetRenderer(Renderer* renderer)
	{
		m_renderer = renderer;
	}
}