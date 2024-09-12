#include "Mouse.h"

namespace vstmr {

	bool Mouse::Pressed(int button)
	{
		return m_mouse_pressed[button];
	}

	bool Mouse::Held(int button)
	{
		return m_mouse_held[button];
	}

	float Mouse::GetX() const
	{
		return m_mousex;
	}

	float Mouse::GetY() const
	{
		return m_mousey;
	}

	float Mouse::ChangeX() const
	{
		return m_mouse_changex;
	}

	float Mouse::ChangeY() const
	{
		return m_mouse_changey;
	}

	float Mouse::ScrollX()
	{
		double scrollx = m_scrollx;
		m_scrolly = 0.0;
		return scrollx;
	}

	float Mouse::ScrollY()
	{
		double scrollx = m_scrolly;
		m_scrolly = 0.0;
		return scrollx;
	}

	void Mouse::Update()
	{
		m_mouse_pressed.reset();
		m_mouse_changex = m_mousex - m_last_mousex;
		m_mouse_changey = m_last_mousey - m_mousey;
		m_last_mousex = m_mousex;
		m_last_mousey = m_mousey;
	}

	void Mouse::OnMouseMove(int x, int y)
	{
		m_mousex = static_cast<float>(x);
		m_mousey = static_cast<float>(y);
	}

	void Mouse::OnMouseScroll(int x, int y)
	{
		m_scrollx = static_cast<float>(x);
		m_scrolly = static_cast<float>(y);
	}

	void Mouse::OnMousePress(int button)
	{
		m_mouse_pressed[button] = true;
	}

	void Mouse::OnMouseHeld(int button)
	{
		m_mouse_held[button] = true;
	}

	void Mouse::OnMouseRelease(int button)
	{
		m_mouse_held[button] = false;
	}

}