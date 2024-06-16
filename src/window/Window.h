#pragma once

#include <bitset>

#include "glfw/glfw3.h"

namespace vstm {

	class Window
	{
		friend void keyCallback(GLFWwindow*, int, int, int, int);
	public:
		Window() = default;
		Window(int width, int height, const char* title,
			GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		~Window();

	public:
		void Update();
		bool IsClosed();
		bool KeyPressed(int key);
		bool KeyHeld(int key);

	private:
		void OnKeyPressed(int key);
		void OnKeyHeld(int key);
		void OnKeyRelease(int key);

	private:
		static constexpr int keyCodes = 348;
		std::bitset<keyCodes> m_keys_pressed;
		std::bitset<keyCodes> m_keys_held;
		GLFWwindow* m_pwindow;
	};

}