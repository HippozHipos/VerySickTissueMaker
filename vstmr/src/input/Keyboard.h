#pragma once
#include "pch.h"
#include "ECS/SceneContainer.h"

class GLFWwindow;
namespace be {

	class Keyboard : public SceneContainer
	{
		friend class Window;
		friend void keyCallback(GLFWwindow*, int, int, int, int);
	public:
		Keyboard() = default;
		~Keyboard() = default;

	public:
		bool Pressed(int key) const;
		bool Held(int key) const;
		void ResetKeysPressed();

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
