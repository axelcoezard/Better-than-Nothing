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
#include "Core/Window/WindowBuilder.h"
#include "Core/Window/Window.h"
#include "Core/Render/Renderer.h"

#include "Events/EventDispatcher.h"
#include "Events/WindowCloseEvent.h"

int main(void) {
	Window* window = Window::GetBuilder()
		->WithTitle("better than nothing")
		->WithSize(720, 720)
		->Build();

	Renderer* renderer = new Renderer(window);

	window->Open();
	while (!window->ShouldClose()) {
		glfwPollEvents();

		renderer->Update();
		renderer->Render();

		window->SwapBuffers();
	}

	GarbageCollector::Destroy();
	return 0;
}
