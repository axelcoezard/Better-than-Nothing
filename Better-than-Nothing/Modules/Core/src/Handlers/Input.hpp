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
		 * @param action The
		 */
		static void UpdateMouseButton(int button, int action);
		static void PressMouseButton(int button);
		static void ReleaseMouseButton(int button);

		static void UpdateMousePosition(f64 x, f64 y);
		static glm::vec2 GetMousePosition();
		static glm::vec2 GetLastMousePosition();
		static glm::vec2 GetMouseDelta();

		static void UpdateMouseScroll(f64 y);
		static f64 GetMouseScroll(void);

		static bool IsKeyPressed(int key);
		static bool IsMouseButtonPressed(int button);
	};
};
