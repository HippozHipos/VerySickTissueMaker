#pragma once

#include <bitset>

#include "ECS/SceneContainer.h"

class GLFWwindow;
namespace be {

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
		bool Pressed(int button);
		bool Held(int button);

		float GetX() const;
		float GetY() const;
		float ChangeX() const;
		float ChangeY() const;
		float ScrollX();
		float ScrollY();

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