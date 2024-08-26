#pragma once

#include <bitset>
#include <glfw/glfw3.h>

#include "vstmr/LayerStack.h"

namespace vstmr {

	class Window
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
		double GetScrollX();
		double GetScrollY();

		inline double GetWidth();
		inline double GetHeight();

		void GetCursorPos(double& xpos, double& ypos);
		void CenterCursorPos(double& last_xpos, double& last_ypos);
		void SetCursorPos(double& last_xpos, double& last_ypos);

		bool MouseButtonPressed(int button);
		bool MouseButtonHeld(int button);

		GLFWwindow* GetGLFWWindow();

		LayerStack& GetLayerStack();

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

		LayerStack m_layer_stack;

		static constexpr int buttonCodes = 5;
		std::bitset<keyCodes> m_mouse_pressed;
		std::bitset<keyCodes> m_mouse_held;
		double m_mousex = 0;
		double m_mousey = 0;
		double m_scrollx = 0;
		double m_scrolly = 0;

		double m_width;
		double m_height;

		GLFWwindow* m_pwindow;
	};

}