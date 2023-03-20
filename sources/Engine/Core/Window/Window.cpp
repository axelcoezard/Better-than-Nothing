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
#include "Events/KeyEvent.h"

Window::Window(std::string_view title, uint32_t width, uint32_t height)
	: m_title(title), m_width(width), m_height(height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	m_Window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glewInit();
}

Window::~Window(void) {
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Open(void) {
	m_Window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
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
			case GLFW_RELEASE:
				event = new KeyReleaseEvent(key, scancode, mods);
				break;
		};

		if (event != nullptr) {
			EventDispatcher* dispatcher = new EventDispatcher(event);
			instance.m_eventCallback(dispatcher, event);
			delete dispatcher;
		}
	});

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	glDepthFunc(GL_LESS);
	glfwSwapInterval(1);
}

void Window::Close(void) {
	glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

bool Window::ShouldClose(void)  {
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

void Window::SwapBuffers(void) {
	glfwSwapBuffers(m_Window);
}

void Window::SetEventCallback(std::function<void(EventDispatcher*, Event*)> eventcallback) {
	m_eventCallback = eventcallback;
}

WindowBuilder* Window::GetBuilder(void) {
	return new WindowBuilder();
}
