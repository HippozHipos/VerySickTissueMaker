#include "Keyboard.h"

namespace be {

	bool Keyboard::Pressed(int key) const
	{
		return m_keys_pressed[key];
	}

	bool Keyboard::Held(int key) const
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

	void Keyboard::ResetKeysPressed()
	{
		m_keys_pressed.reset();
	}

}