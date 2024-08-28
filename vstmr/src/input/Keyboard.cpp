#include "Keyboard.h"

namespace vstmr {

	bool Keyboard::KeyPressed(int key) const
	{
		return m_keys_pressed[key];
	}

	bool Keyboard::KeyHeld(int key) const
	{
		return m_keys_held[key];
	}

	void Keyboard::OnKeyPress(int key)
	{
		m_keys_pressed[key] = true;
	}

	void Keyboard::OnKeyHeld(int key)
	{
		m_keys_held[key] = true;
	}

	void Keyboard::OnKeyRelease(int key)
	{
		m_keys_held[key] = false;
	}

}