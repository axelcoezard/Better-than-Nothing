#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief The window class that is a wrapper around GLFWwindow and handles some events
	 */
	class Window
	{
	private:
		/**
		 * @brief The GLFWwindow pointer
		 */
		GLFWwindow* m_Window;

		/**
		 * @brief The title of the window
		 */
		std::string m_Title;

		/**
		 * @brief The width of the window
		 */
		u32 m_Width;

		/**
		 * @brief The height of the window
		 */
		u32 m_Height;

		/**
		 * @brief If the window is resized
		 */
		bool m_Resized = false;

		/**
		 * @brief The event callback
		 */
		std::function<void(Event*)>	m_EventCallback;

	public:
		/**
		 * @brief The window constructor
		 * @param title The title of the window
		 * @param width The width of the window
		 * @param height The height of the window
		 */
		Window(std::string_view title, u32 width, u32 height);

		/**
		 * @brief The window destructor
		 */
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		/**
		 * @brief A wrapper around glfwPollEvents that polls for events
		 */
		void Poll() { glfwPollEvents(); }

		/**
		 * @brief A wrapper around glfwWindowShouldClose
		 * @return If the window should close
		 */
		bool ShouldClose() { return glfwWindowShouldClose(m_Window) ==  GLFW_TRUE; }

		/**
		 * @brief A wrapper around glfwSetWindowShouldClose that sets the window to close
		 */
		void Close() { glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

		/**
		 * @brief Sets the event callback
		 */
		void SetEventCallback(std::function<void(Event*)> eventcallback);

		/**
		 * @brief Called when the window is resized
		 * @param window The GLFW window that is resized
		 * @param width The new width of the window
		 * @param height The new height of the window
		 */
		static void ResizeCallback(GLFWwindow* window, int width, int height);

		/**
		 * @brief Called when a key is pressed or released
		 * @param window The GLFW window that is resized
		 * @param key The key that is pressed
		 * @param scancode The scancode of the key
		 * @param action The action of the key (PRESS, RELEASE, REPEAT)
		 * @param mods The mods of the key
		 */
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		 * @brief Called when the mouse cursor is moved
		 * @param window The GLFW window that is resized
		 * @param xpos The x position of the mouse cursor
		 * @param ypos The y position of the mouse cursor
		 */
		static void MouseCursorCallback(GLFWwindow* window, f64 xpos, f64 ypos);

		/**
		 * @brief Called when the mouse is scrolled
		 * @param window The GLFW window that is resized
		 * @param xoffset The x offset of the mouse scroll
		 * @param yoffset The y offset of the mouse scroll
		 */
		static void MouseScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset);

		/**
		 * @brief Called when a mouse button is pressed or released
		 * @param window The GLFW window that is resized
		 * @param button The button that is pressed
		 * @param action The action of the button (PRESS, RELEASE, REPEAT)
		 * @param mods The mods of the button
		 */
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		/**
		 * @brief Gets the GLFWwindow pointer
		 * @return The GLFWwindow pointer
		 */
		GLFWwindow* GetPointer() { return m_Window; }

		/**
		 * @brief Gets the title of the window
		 * @return The title of the window
		 */
		std::string& GetTitle() { return m_Title; }

		/**
		 * @brief Gets the width of the window
		 * @return The width of the window
		 */
		u32 GetWidth() { return m_Width; }

		/**
		 * @brief Gets the height of the window
		 * @return The height of the window
		 */
		u32 GetHeight() { return m_Height; }

		/**
		 * @brief Gets if the window is resized
		 * @return Whether the window is resized or not
		 */
		bool IsResized() { return m_Resized; }

		/**
		 * @brief Sets if the window is resized
		 */
		void SetResized(bool resized) { m_Resized = resized; }
	};
};
