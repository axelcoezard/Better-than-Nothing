#include "Engine/Window.hpp"
#include "Handlers/Input.hpp"

namespace BetterThanNothing
{
	Window::Window(std::string_view title, uint32_t width, uint32_t height)
		: m_pWindow(nullptr), m_Title(title), m_Width(width), m_Height(height)
	{
		Open();
	}

	Window::~Window()
	{
		if (m_pWindow != nullptr) {
			glfwDestroyWindow(m_pWindow);
			glfwTerminate();
		}
	}

	void Window::Open()
	{
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_pWindow, this);
		glfwSetFramebufferSizeCallback(m_pWindow, ResizeCallback);
		glfwSetKeyCallback(m_pWindow, KeyCallback);
		glfwSetCursorPosCallback(m_pWindow, MouseCursorCallback);
		glfwSetScrollCallback(m_pWindow, MouseScrollCallback);
		glfwSetMouseButtonCallback(m_pWindow, MouseButtonCallback);
	}

	void Window::SetEventCallback(std::function<void(Event*)>& eventcallback)
	{
		m_eventCallback = eventcallback;
	}

	void Window::ResizeCallback(GLFWwindow* pWindow, int width, int height)
	{
		(void) width;
		(void) height;

		auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(pWindow));
		window->SetResized(true);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		(void) scancode;
		(void) mods;

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		Input::UpdateKey(key, action);
	}

	void Window::MouseCursorCallback(GLFWwindow* window, double xpos, double ypos)
	{
		(void) window;
		Input::UpdateMousePosition(xpos, ypos);
	}

	void Window::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		(void) window;
		(void) xoffset;
		Input::UpdateMouseScroll(yoffset);
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		(void) window;
		(void) mods;
		Input::UpdateMouseButton(button, action);
	}
};
