#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/WindowBuilder.h"
#include "Core/Window.h"

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
	return 0;
}
