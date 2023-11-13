#include "Renderer/Window.hpp"
#include "Handlers/Input.hpp"
#include "Events/KeyEvent.hpp"

namespace BetterThanNothing
{
	Window::Window(std::string_view title, u32 width, u32 height)
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

	void Window::SetEventCallback(std::function<void(Event*)> eventcallback)
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

		if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		Input::UpdateKey(key, action);

		auto pWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

		KeyEvent* event = nullptr;
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			event = new KeyPressEvent(key, scancode, mods);
		} else {
			event = new KeyReleaseEvent(key, scancode, mods);
		}

		if (event != nullptr) {
			pWindow->m_eventCallback(event);
		}
	}

	void Window::MouseCursorCallback(GLFWwindow* window, f64 xpos, f64 ypos)
	{
		(void) window;
		Input::UpdateMousePosition(xpos, ypos);
	}

	void Window::MouseScrollCallback(GLFWwindow* window, f64 xoffset, f64 yoffset)
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
