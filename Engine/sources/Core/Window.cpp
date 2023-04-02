#include "Core/Window.hpp"

#include "Events/EventDispatcher.hpp"
#include "Events/KeyEvent.hpp"

Window::Window(std::string_view title, uint32_t width, uint32_t height)
	: m_Window(nullptr), m_Title(title), m_Width(width), m_Height(height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
#if __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window() {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Open() {
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window& instance = *(Window*) glfwGetWindowUserPointer(window);
		Event* event = nullptr;

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			return (void) instance.Close();
		}

		switch (action) {
			case GLFW_PRESS:
				event = new KeyPressEvent(key, scancode, mods);
				break;
			case GLFW_REPEAT:
				event = new KeyPressEvent(key, scancode, mods);
				break;
			case GLFW_RELEASE:
				event = new KeyReleaseEvent(key, scancode, mods);
				break;
		};

		if (event != nullptr) {
			instance.m_eventCallback(event);
			delete event;
		}
	});

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	glfwSwapInterval(1);
}

void Window::Close() {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

bool Window::ShouldClose()  {
	return glfwWindowShouldClose(m_Window) ==  GLFW_TRUE;
}

void Window::Clear(float red, float green, float blue, float alpha) {
	int width;
	int height;
	glfwGetFramebufferSize(m_Window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(m_Window);
}

void Window::SetEventCallback(std::function<void(Event*)>& eventcallback) {
	m_eventCallback = eventcallback;
}

uint32_t Window::GetWidth() {
	return m_Width;
}
uint32_t Window::GetHeight() {
	return m_Height;
}
