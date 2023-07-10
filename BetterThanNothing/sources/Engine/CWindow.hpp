#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <string_view>
#include <memory>

namespace BetterThanNothing
{
	class CWindow
	{
	private:
		GLFWwindow*		m_pWindow;

		std::string		m_Title;
		uint32_t		m_Width, m_Height;

		bool			m_bResized = false;
	public:
		CWindow(std::string_view title, uint32_t width, uint32_t height);
		~CWindow();

		CWindow(const CWindow&) = delete;
		CWindow& operator=(const CWindow&) = delete;

		void			Open();
		void			Poll()						{ glfwPollEvents(); }
		bool			ShouldClose()				{ return glfwWindowShouldClose(m_pWindow) ==  GLFW_TRUE; }
		void			Close()						{ glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE); }

		static void		ResizeCallback(GLFWwindow* window, int width, int height);

		GLFWwindow*		GetPointer()				{ return m_pWindow; }
		std::string&	GetTitle()					{ return m_Title; }
		uint32_t		GetWidth()					{ return m_Width; }
		uint32_t		GetHeight()					{ return m_Height; }

		bool			IsResized()					{ return m_bResized; }
		void			SetResized(bool bResized)	{ m_bResized = bResized; }
	};
};
