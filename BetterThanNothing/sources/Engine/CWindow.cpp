#include "Engine/Window.hpp"

CWindow::CWindow(std::string_view title, uint32_t width, uint32_t height)
	: m_pWindow(nullptr), m_Title(title), m_Width(width), m_Height(height) {
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

CWindow::~CWindow() {
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void CWindow::Open() {
	m_pWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_pWindow);
	glfwSetWindowUserPointer(m_pWindow, this);

	glfwSetKeyCallback(m_pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		CWindow& instance = *(CWindow*) glfwGetWindowUserPointer(window);
		CEvent* event = nullptr;

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			return (void) instance.Close();
		}

		switch (action) {
			case GLFW_PRESS:
				event = new CKeyPressEvent(key, scancode, mods);
				break;
			case GLFW_REPEAT:
				event = new CKeyPressEvent(key, scancode, mods);
				break;
			case GLFW_RELEASE:
				event = new CKeyReleaseEvent(key, scancode, mods);
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

void CWindow::Close() {
	glfwSetWindowShouldClose(m_pWindow, GLFW_TRUE);
}

bool CWindow::ShouldClose()  {
	return glfwWindowShouldClose(m_pWindow) ==  GLFW_TRUE;
}

void CWindow::Clear(float red, float green, float blue, float alpha) {
	int width;
	int height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CWindow::SwapBuffers() {
	glfwSwapBuffers(m_pWindow);
}

void CWindow::SetEventCallback(std::function<void(CEvent*)>& eventcallback) {
	m_eventCallback = eventcallback;
}

uint32_t CWindow::GetWidth() {
	return m_Width;
}
uint32_t CWindow::GetHeight() {
	return m_Height;
}
