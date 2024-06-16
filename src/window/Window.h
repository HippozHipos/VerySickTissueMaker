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
		void Fill(float r, float g, float b, float a);
		void SetFocus();
		bool IsClosed();
		bool KeyPressed(int key);
		bool KeyHeld(int key);

	private:
		void OnKeyPress(int key);
		void OnKeyHeld(int key);
		void OnKeyRelease(int key);

		void InitOpengl(int width, int height);

	private:
		static constexpr int keyCodes = 348;
		std::bitset<keyCodes> m_keys_pressed;
		std::bitset<keyCodes> m_keys_held;
		GLFWwindow* m_pwindow;
	};

}