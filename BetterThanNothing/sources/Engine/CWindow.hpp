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
	public:
		CWindow(std::string_view title, uint32_t width, uint32_t height);
		~CWindow();

		CWindow(const CWindow&) = delete;
		CWindow& operator=(const CWindow&) = delete;

		void			Open();
		void			Poll();

		bool			ShouldClose();
		void			Close();

		GLFWwindow*		GetPointer();
		std::string&	GetTitle();
		uint32_t		GetWidth();
		uint32_t		GetHeight();
	};
};
