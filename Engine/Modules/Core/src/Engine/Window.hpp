#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class Window
	{
	private:
		GLFWwindow*					m_pWindow;

		std::string					m_Title;
		uint32_t					m_Width, m_Height;

		bool						m_bResized = false;

		std::function<void(Event*)>	m_eventCallback;
	public:
						Window(std::string_view title, uint32_t width, uint32_t height);
						~Window();

						Window(const Window&) = delete;
						Window& operator=(const Window&) = delete;

		void			Open();
		void			Poll()						{ glfwPollEvents(); }
		bool			ShouldClose()				{ return glfwWindowShouldClose(m_pWindow) ==  GLFW_TRUE; }
		void			Close()						{ glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE); }

		void			SetEventCallback(std::function<void(Event*)> eventcallback);

		static void		ResizeCallback(GLFWwindow* window, int width, int height);
		static void		KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void		MouseCursorCallback(GLFWwindow* window, double xpos, double ypos);
		static void		MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void		MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		GLFWwindow*		GetPointer()				{ return m_pWindow; }
		std::string&	GetTitle()					{ return m_Title; }
		uint32_t		GetWidth()					{ return m_Width; }
		uint32_t		GetHeight()					{ return m_Height; }

		bool			IsResized()					{ return m_bResized; }
		void			SetResized(bool bResized)	{ m_bResized = bResized; }
	};
};