#include "Layer.h"
#include "renderer/Viewport.h"

namespace vstmr {

	void Layer::Start() 
	{
	}

	void Layer::Update(float deltaTime)
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

	size_t Layer::NumViewports(size_t i) const
	{
		return m_viewports.size();
	}

	PerspectiveCamera& Layer::GetCamera()
	{
		return m_camera;
	}

	std::shared_ptr<Viewport> Layer::AddViewport(int x, int y, int width, int height)
	{
		m_viewports.push_back(std::make_unique<Viewport>(x, y, width, height));
		return m_viewports.back();
	}

	Viewport* Layer::GetViewport(size_t i)
	{
		return m_viewports[i].get();
	}
}