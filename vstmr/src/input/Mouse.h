#pragma once

#include <bitset>

#include "ECS/SceneContainer.h"

class GLFWwindow;
namespace vstmr {

	class Mouse : public SceneContainer
	{
		friend class Window;
		friend void mouseButtonCallback(GLFWwindow*, int, int, int);
		friend void mousePositionCallback(GLFWwindow*, double, double);
		friend void scrollWheelCallback(GLFWwindow*, double, double);
	public:

		Mouse() = default;
		~Mouse() = default;

	public:
		bool MouseButtonPressed(int button);
		bool MouseButtonHeld(int button);

		float GetMouseX() const;
		float GetMouseY() const;
		float GetMouseChangeX() const;
		float GetMouseChangeY() const;
		float GetScrollX();
		float GetScrollY();

		void Update();

	private:
		void OnMouseMove(int x, int y);
		void OnMouseScroll(int x, int y);
		void OnMousePress(int button);
		void OnMouseHeld(int button);
		void OnMouseRelease(int button);

	private:
		float m_mousex, m_mousey = 0;
		float m_scrollx, m_scrolly = 0;
		float m_last_mousex, m_last_mousey = 0;
		float m_mouse_changex, m_mouse_changey = 0;

		static constexpr int buttonCodes = 5;
		std::bitset<buttonCodes> m_mouse_pressed;
		std::bitset<buttonCodes> m_mouse_held;
	};

}