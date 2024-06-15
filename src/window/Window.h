#pragma once

#include "glfw/glfw3.h"

namespace vstm {

	class Window
	{
	public:
		Window() = default;
		Window(int width, int height, const char* title,
			GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		~Window();

	public:
		bool IsClosed();

	private:
		GLFWwindow* m_pwindow;
	};

}