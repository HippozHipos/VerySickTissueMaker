#include "Mouse.h"

namespace vstmr {

	bool Mouse::MouseButtonPressed(int button)
	{
		return m_mouse_pressed[button];
	}

	bool Mouse::MouseButtonHeld(int button)
	{
		return m_mouse_held[button];
	}

	float Mouse::GetMouseX() const
	{
		return m_mousex;
	}

	float Mouse::GetMouseY() const
	{
		return m_mousey;
	}

	float Mouse::GetMouseChangeX() const
	{
		return m_mouse_changex;
	}

	float Mouse::GetMouseChangeY() const
	{
		return m_mouse_changey;
	}

	float Mouse::GetScrollX()
	{
		double scrollx = m_scrollx;
		m_scrolly = 0.0;
		return scrollx;
	}

	float Mouse::GetScrollY()
	{
		double scrollx = m_scrolly;
		m_scrolly = 0.0;
		return scrollx;
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