#pragma once
#include "pch.h"

#ifndef GLFW_INCLUDE_NONE 
	#define GLFW_INCLUDE_NONE 
#endif
#include <glfw/glfw3.h>

#include "ECS/SceneContainer.h"

#include "Input/Keyboard.h"
#include "Input/Mouse.h"

namespace be {

	class MainPlatformWindow : public SceneContainer
	{
		friend void keyCallback(GLFWwindow*, int, int, int, int);
		friend void mouseButtonCallback(GLFWwindow*, int, int, int);
		friend void mousePositionCallback(GLFWwindow*, double, double);
		friend void scrollWheelCallback(GLFWwindow*, double, double);
		friend void frameBufferSizeCallback(GLFWwindow*, int, int);
	public:
		MainPlatformWindow() = default;
		MainPlatformWindow(int width, int height, const char* title, Keyboard& keyboard, Mouse& mouse,
			GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

	public:
		void Update();
		void SetFocus();
		bool IsClosed();

		float GetWidth();
		float GetHeight();

		void SetCursorPos(float x, float y);

		void DisableCursor();
		void DefaultCursor();

		GLFWwindow* GetGLFWWindow();

	private:
		void InitOpengl(int width, int height);

	private:
		Keyboard& m_keyboard;
		Mouse& m_mouse;

		int m_width;
		int m_height;

		GLFWwindow* m_pwindow;
	};

}