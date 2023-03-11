/*
 * File: Window.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:29:40 pm
 * Last Modified: Tuesday, 7th March 2023 7:50:48 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */
#include <iostream>

#include "Core/Window/Window.h"
#include "Core/Window/WindowBuilder.h"

#include "Events/EventDispatcher.h"
#include "Events/WindowCloseEvent.h"

Window::Window(std::string_view title, uint32_t width, uint32_t height) {
	m_data.m_title = std::string(title);
	m_data.m_width = width;
	m_data.m_height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	SetEventCallback(EVENT_LISTENER(onEvent));
}

Window::~Window(void) {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::Open(void) {
	m_window = glfwCreateWindow(m_data.m_width, m_data.m_height, m_data.m_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, &m_data);

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
		(void) scancode;
		(void) mods;
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			data.m_eventCallback(new WindowCloseEvent());
		}
	});

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glDepthFunc(GL_LESS);
	glfwSwapInterval(1);
}

void Window::onEvent(Event* event)  {
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowCloseEvent>(EVENT_LISTENER(onWindowCloseEvent));
}

bool Window::onWindowCloseEvent(WindowCloseEvent* event) {
	(void) event;
	std::cout << "closing window" << std::endl;
	return true;
}

bool Window::ShouldClose(void)  {
	return glfwWindowShouldClose(m_window) ==  GLFW_TRUE;
}

void Window::Clear(void) {
	int width;
	int height;
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, width, height);
	// TODO: Add clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers(void) {
	glfwSwapBuffers(m_window);
}

void Window::Close(void) {
	glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::SetEventCallback(std::function<void(Event*)> eventcallback) {
	m_data.m_eventCallback = eventcallback;
}

WindowBuilder* Window::GetBuilder(void) {
	return new WindowBuilder();
}
