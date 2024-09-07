#pragma once

#include <bitset>
#include <glfw/glfw3.h>

#include "ECS/SceneContainer.h"

namespace vstmr {

	class Window : public SceneContainer
	{
		friend void keyCallback(GLFWwindow*, int, int, int, int);
		friend void mouseButtonCallback(GLFWwindow*, int, int, int);
		friend void mousePositionCallback(GLFWwindow*, double, double);
		friend void scrollWheelCallback(GLFWwindow*, double, double);
		friend void frameBufferSizeCallback(GLFWwindow*, int, int);
	public:
		Window() = default;
		Window(int width, int height, const char* title,
			GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

	public:
		void Update();
		void SetFocus();
		bool IsClosed();
		bool KeyPressed(int key);
		bool KeyHeld(int key);
		
		float GetMouseX();
		float GetMouseY();
		float GetMouseChangeX();
		float GetMouseChangeY();
		float GetScrollX();
		float GetScrollY();

		float GetWidth();
		float GetHeight();

		void SetCursorPos(float x, float y);

		bool MouseButtonPressed(int button);
		bool MouseButtonHeld(int button);

		void DisableCursor();
		void DefaultCursor();

		void ClearColor(float r, float g, float b, float a);

		GLFWwindow* GetGLFWWindow();

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

		float m_mousex, m_mousey = 0;
		float m_scrollx, m_scrolly = 0;
		float m_last_mousex, m_last_mousey = 0;
		float m_mouse_changex, m_mouse_changey = 0;

		int m_width;
		int m_height;

		GLFWwindow* m_pwindow;
	};

}