#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	GLFWwindow* window = glfwCreateWindow(720, 480, "OpenGL tutorial", nullptr, nullptr);

	if (window == nullptr) {
		std::cerr << "Window init failed..." << std::endl;
		glfwTerminate ();
		return -2;
	}

	glfwMakeContextCurrent (window);

	if (glewInit () != GLEW_OK) {
		std::cerr << "Glew init failed..." << std::endl;
		glfwDestroyWindow (window);
		glfwTerminate ();
		return -3;
	}


	int width;
	int height;
	while (!glfwWindowShouldClose (window)) {
		glfwPollEvents ();

		glfwGetFramebufferSize (window, &width, &height);
		glViewport (0, 0, width, height);
		glClearColor (0.2f, 0.2f, 0.45f, 1.0f);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers (window);
	}
	glfwDestroyWindow (window);
	glfwTerminate ();

	return 0;
}
