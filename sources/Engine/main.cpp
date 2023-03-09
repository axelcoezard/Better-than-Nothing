/*
 * File: main.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 6:00:12 pm
 * Last Modified: Tuesday, 7th March 2023 9:49:41 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/GarbageCollector/GarbageCollector.h"

#include "Core/WindowBuilder.h"
#include "Core/Window.h"

#include "Events/EventDispatcher.h"

int main(void) {
	Window* window = Window::GetBuilder()
		->WithTitle("better than nothing")
		->WithSize(720, 720)
		->Build();

	while (!window->ShouldClose()) {
		glfwPollEvents();

		window->SwapBuffers();
	}

	GarbageCollector::Destroy();
	return 0;
}
