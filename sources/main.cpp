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

#include "Core/WindowBuilder.h"
#include "Core/Window.h"

#include "Events/EventDispatcher.h"

int main(void) {
	WindowBuilder windowBuilder;
	windowBuilder.WithTitle("better than nothing");
	windowBuilder.WithSize(720, 720);
	Window* window = windowBuilder.Build();

	while (!window->ShouldClose()) {
		glfwPollEvents();

		window->SwapBuffers();
	}

	delete window;
	EventDispatcher::Destroy();
	return 0;
}
