#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class Window
	{
	private:
		GLFWwindow*					m_Window;

		std::string					m_Title;
		u32							m_Width, m_Height;

		bool						m_Resized = false;

		std::function<void(Event*)>	m_EventCallback;
	public:
						Window(std::string_view title, u32 width, u32 height);
						~Window();

						Window(const Window&) = delete;
						Window& operator=(const Window&) = delete;

		void			Poll()						{ glfwPollEvents(); }
		bool			ShouldClose()				{ return glfwWindowShouldClose(m_Window) ==  GLFW_TRUE; }
		void			Close()						{ glfwSetWindowShouldClose(m_Window, GLFW_TRUE); }

		void			SetEventCallback(std::function<void(Event*)> eventcallback);

		static void		ResizeCallback(GLFWwindow* window, int width, int height);
		static void		KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void		MouseCursorCallback(GLFWwindow* window, f64 xpos, f64 ypos);
		static void		MouseScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset);
		static void		MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		GLFWwindow*		GetPointer()				{ return m_Window; }
		std::string&	GetTitle()					{ return m_Title; }
		u32		GetWidth()					{ return m_Width; }
		u32		GetHeight()					{ return m_Height; }

		bool			IsResized()					{ return m_Resized; }
		void			SetResized(bool resized)	{ m_Resized = resized; }
	};
};
