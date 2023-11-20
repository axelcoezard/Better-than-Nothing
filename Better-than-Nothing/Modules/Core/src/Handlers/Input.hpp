#pragma once

#define KEYBOARD_KEY_COUNT 1024
#define MOUSE_BUTTON_COUNT 32

namespace BetterThanNothing
{
	/**
	 * @brief The Input class is the base class of all input management
	 */
	struct Input {
	protected:
		/**
		 * @brief The keys
		 */
		static int m_Keys[KEYBOARD_KEY_COUNT];

		/**
		 * @brief The mouse X position
		 */
		static f64 m_MouseX;


		/**
		 * @brief The mouse X position
		 */
		static f64 m_MouseY;

		/**
		 * @brief The last mouse X position
		 */
		static f64 m_LastMouseX;

		/**
		 * @brief The last mouse Y position
		 */
		static f64 m_LastMouseY;

		/**
		 * @brief The mouse scroll
		 */
		static f64 m_MouseScroll;

		/**
		 * @brief The mouse buttons
		 */
		static int m_Buttons[MOUSE_BUTTON_COUNT];

	public:
		/**
		 * @brief Construct a new Input object
		 */
		Input(void);

		/**
		 * @brief Destroy the Input object
		 */
		~Input(void);

		/**
		 * @brief Delete the copy constructor
		 */
		Input(Input&) = delete;

		/**
		 * @brief Delete the assignment operator
		 */
		void operator=(const Input&) = delete;

		/**
		 * @brief Update the input key
		 */
		static void UpdateKey(int key, int action);

		/**
		 * @brief Set a key as pressed
		 * @param key The key to set as pressed
		 */
		static void PressKey(int key);

		/**
		 * @brief Set a key as released
		 * @param key The key to set as released
		 */
		static void ReleaseKey(int key);

		/**
		 * @brief Update a mouse button
		 * @param button The button to update
		 * @param action The action of the button
		 */
		static void UpdateMouseButton(int button, int action);

		/**
		 * @brief Set a mouse button as pressed
		 * @param button The button to set as pressed
		 */
		static void PressMouseButton(int button);

		/**
		 * @brief Set a mouse button as released
		 * @param button The button to set as released
		 */
		static void ReleaseMouseButton(int button);

		/**
		 * @brief Update the mouse position
		 * @param x The X position of the mouse
		 * @param y The Y position of the mouse
		 */
		static void UpdateMousePosition(f64 x, f64 y);

		/**
		 * @brief Get the mouse position
		 * @return The mouse position vector
		 */
		static glm::vec2 GetMousePosition();

		/**
		 * @brief Get the last mouse position
		 * @return The last mouse position vector
		 */
		static glm::vec2 GetLastMousePosition();

		/**
		 * @brief Get the mouse delta
		 * @return The mouse delta vector
		 */
		static glm::vec2 GetMouseDelta();

		/**
		 * @brief Update the mouse scroll
		 * @param y The Y scroll of the mouse
		 */
		static void UpdateMouseScroll(f64 y);

		/**
		 * @brief Get the mouse scroll
		 * @return The mouse scroll
		 */
		static f64 GetMouseScroll(void);

		/**
		 * @brief Check if a key is pressed
		 * @param key The key to check
		 * @return true if the key is pressed, false otherwise
		 */
		static bool IsKeyPressed(int key);

		/**
		 * @brief Check if a mouse button is pressed
		 * @param button The button to check
		 * @return true if the button is pressed, false otherwise
		 */
		static bool IsMouseButtonPressed(int button);
	};
};
