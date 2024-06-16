#pragma once

#include <bitset>

#include "glfw/glfw3.h"

namespace vstm {



	class Window
	{
		friend void keyCallback(GLFWwindow*, int, int, int, int);
		friend void mouseButtonCallback(GLFWwindow*, int, int, int);
		friend void mousePositionCallback(GLFWwindow*, double, double);
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
		
		double GetMouseX();
		double GetMouseY();


		bool MouseButtonPressed(int button);
		bool MouseButtonHeld(int button);

	private:
		void OnKeyPress(int key);
		void OnKeyHeld(int key);
		void OnKeyRelease(int key);

		void OnMousePress(int button);
		void OnMouseHeld(int button);
		void OnMouseRelease(int button);

		void InitOpengl(int width, int height);

	private:
		static constexpr int keyCodes = 348;
		std::bitset<keyCodes> m_keys_pressed;
		std::bitset<keyCodes> m_keys_held;

		static constexpr int buttonCodes = 5;
		std::bitset<keyCodes> m_mouse_pressed;
		std::bitset<keyCodes> m_mouse_held;
		double m_mouseX = 0;
		double m_mouseY = 0;

		GLFWwindow* m_pwindow;
	};

}