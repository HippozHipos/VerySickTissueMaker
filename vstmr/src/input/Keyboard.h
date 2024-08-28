#pragma once

#include <bitset>

namespace vstmr {

	//forward declare for callback
	class GLFWwindow;

	class Keyboard
	{
		friend class Window;
		friend void keyCallback(GLFWwindow*, int, int, int, int);
	public:
		Keyboard() = default;
		~Keyboard() = default;

	public:
		bool KeyPressed(int key) const;
		bool KeyHeld(int key) const;

	private:
		void OnKeyPress(int key);
		void OnKeyHeld(int key);
		void OnKeyRelease(int key);

	private:
		static constexpr int keyCodes = 348;
		std::bitset<keyCodes> m_keys_pressed;
		std::bitset<keyCodes> m_keys_held;
	};

}
