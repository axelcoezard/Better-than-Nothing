/*
 * File: Window.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:29:40 pm
 * Last Modified: Tuesday, 7th March 2023 7:50:48 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Core/Window/Window.h"
#include "Core/Window/WindowBuilder.h"

Window::Window(std::string_view title, uint32_t width, uint32_t height)
	: m_title(title), m_width(width), m_height(height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	m_window = glfwCreateWindow(width, height, m_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_window);
	glewInit();
}

Window::~Window(void) {
	glfwDestroyWindow(m_window);
	glfwTerminate();
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

WindowBuilder* Window::GetBuilder(void) {
	return new WindowBuilder();
}
