#include "Engine/CWindow.hpp"

namespace BetterThanNothing
{
	CWindow::CWindow(std::string_view title, uint32_t width, uint32_t height)
		: m_pWindow(nullptr), m_Title(title), m_Width(width), m_Height(height) {}

	CWindow::~CWindow() {
		if (m_pWindow != nullptr) {
			glfwDestroyWindow(m_pWindow);
			glfwTerminate();
		}
	}

	void CWindow::Open() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	}

	void CWindow::Poll()				{ glfwPollEvents(); }

	bool CWindow::ShouldClose()			{ return glfwWindowShouldClose(m_pWindow) ==  GLFW_TRUE; }

	void CWindow::Close()				{ glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE); }

	GLFWwindow* CWindow::GetPointer()	{ return m_pWindow; }

	uint32_t CWindow::GetWidth()		{ return m_Width; }

	uint32_t CWindow::GetHeight()		{ return m_Height; }
};
