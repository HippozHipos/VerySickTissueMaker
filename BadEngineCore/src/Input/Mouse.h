#pragma once
#include "pch.h"

#include "ECS/SceneContainer.h"

class GLFWwindow;
namespace be {

	/**
	 * \class Mouse
	 * \brief Manages the state of mouse inputs for "Main Platform Window" i.e. Window class.
	 *
	 * The Mouse class tracks mouse button presses, holds, and movement. It interacts with GLFW
	 * to handle mouse position, button states, and scroll wheel movements. The class provides methods
	 * to query the mouse state and update internal data accordingly.
	 */
	class Mouse : public SceneContainer
	{
		friend class Window;
		friend void mouseButtonCallback(GLFWwindow*, int, int, int);
		friend void mousePositionCallback(GLFWwindow*, double, double);
		friend void scrollWheelCallback(GLFWwindow*, double, double);

	public:
		/**
		 * \brief Default constructor for the Mouse class.
		 */
		Mouse() = default;
		/**
		 * \brief Default destructor for the Mouse class.
		 */
		~Mouse() = default;

	public:
		/**
		* \brief Checks if a mouse button was pressed.
		*
		* \param button The button code to check.
		* \return true if the button was pressed in the current frame, false otherwise.
		*/
		bool Pressed(int button);
		/**
		 * \brief Checks if a mouse button is being held down.
		 *
		 * \param button The button code to check.
		 * \return true if the button is being held down, false otherwise.
		 */
		bool Held(int button);

		/**
		 * \brief Gets the current X position of the mouse.
		 *
		 * \return The current X coordinate of the mouse.
		 */
		float GetX() const;
		/**
		* \brief Gets the current Y position of the mouse.
		*
		* \return The current Y coordinate of the mouse.
		*/
		float GetY() const;
		/**
		 * \brief Gets the change in X position since the last update.
		 *
		 * \return The change in the X coordinate of the mouse.
		 */
		float ChangeX() const;
		/**
		 * \brief Gets the change in Y position since the last update.
		 *
		 * \return The change in the Y coordinate of the mouse.
		 */
		float ChangeY() const;
		/**
		 * \brief Gets the horizontal scroll value.
		 *
		 * \return The current scroll X value.
		 */
		float ScrollX();
		/**
		* \brief Gets the vertical scroll value.
		*
		* \return The current scroll Y value.
		*/
		float ScrollY();
		/**
		 * \brief Updates the mouse state, including movement and button states.
		 */
		void Update();

	private:
		/**
		 * \brief Updates the internal state when the mouse moves.
		 *
		 * \param x The new X coordinate of the mouse.
		 * \param y The new Y coordinate of the mouse.
		 */
		void OnMouseMove(int x, int y);
		/**
		* \brief Updates the internal state when the scroll wheel is used.
		*
		* \param x The horizontal scroll amount.
		* \param y The vertical scroll amount.
		*/
		void OnMouseScroll(int x, int y);
		/**
		 * \brief Updates the internal state when a mouse button is pressed.
		 *
		 * \param button The button code that was pressed.
		 */
		void OnMousePress(int button);
		/**
		 * \brief Updates the internal state when a mouse button is held.
		 *
		 * \param button The button code that is being held down.
		 */
		void OnMouseHeld(int button);
		/**
		 * \brief Updates the internal state when a mouse button is released.
		 *
		 * \param button The button code that was released.
		 */
		void OnMouseRelease(int button);

	private:
		float m_mousex, m_mousey = 0;///< The current mouse X and Y coordinates.
		float m_scrollx, m_scrolly = 0;///< The current scroll X and Y values.
		float m_last_mousex, m_last_mousey = 0;///< The last recorded mouse X and Y coordinates.
		float m_mouse_changex, m_mouse_changey = 0;///< The change in mouse X and Y coordinates.

		static constexpr int buttonCodes = 5;///< The number of mouse buttons supported by the class.
		std::bitset<buttonCodes> m_mouse_pressed;///< Bitset representing mouse buttons pressed in the current frame.
		std::bitset<buttonCodes> m_mouse_held;///< Bitset representing mouse buttons being held down.
	};

}