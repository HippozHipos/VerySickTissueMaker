#pragma once
#include "pch.h"
#include "ECS/SceneContainer.h"

class GLFWwindow;
namespace be {

	/**
	 * \class Keyboard
	 * \brief Manages the state of keyboard inputs for the "Main Platform Window" i.e. Window class.
	 *
	 * The Keyboard class tracks key press, hold, and release states. It interacts with GLFW through
	 * a callback to update key states, and provides methods to query whether keys are pressed or held.
	 * It uses a bitset to store the state of all keys.
	 */
	class Keyboard : public SceneContainer
	{
		//friend class MainPlatformWindow;
		friend void keyCallback(GLFWwindow*, int, int, int, int);
	public:
		/**
		* \brief Default constructor for the Keyboard class.
		*/
		Keyboard() = default;
		/**
		 * \brief Default destructor for the Keyboard class.
		 */
		~Keyboard() = default;

	public:
		/**
		 * \brief Checks if a key was pressed.
		 *
		 * \param key The key code to check.
		 * \return true if the key was pressed in the current frame, false otherwise.
		 */
		bool Pressed(int key) const;
		/**
		 * \brief Checks if a key is currently being held down.
		 *
		 * \param key The key code to check.
		 * \return true if the key is being held down, false otherwise.
		 */
		bool Held(int key) const;
		/**
		 * \brief Resets the state of keys that were pressed.
		 *
		 * Clears the pressed keys bitset, effectively resetting the pressed state for all keys.
		 */
		void ResetKeysPressed();

	private:
		/**
		 * \brief Updates the internal state when a key is pressed.
		 *
		 * \param key The key code that was pressed.
		 */
		void OnKeyPress(int key);
		/**
		 * \brief Updates the internal state when a key is held.
		 *
		 * \param key The key code that is being held.
		 */
		void OnKeyHeld(int key);
		/**
		 * \brief Updates the internal state when a key is released.
		 *
		 * \param key The key code that was released.
		 */
		void OnKeyRelease(int key);

	private:
		static constexpr int keyCodes = 348;///< The number of key codes supported by the class.
		std::bitset<keyCodes> m_keys_pressed;///< Bitset representing keys pressed in the current frame.
		std::bitset<keyCodes> m_keys_held;///< Bitset representing keys that are being held down.
	};

}
