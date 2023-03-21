/*
 * File: main.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 6:00:12 pm
 * Last Modified: Tuesday, 7th March 2023 9:49:41 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/Buffer.h"

static Window* m_Window;
static Renderer* m_Renderer;

int main(void) {
	m_Window = new Window("better than nothing", 720, 720);
	//m_Window->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));
	m_Renderer = new Renderer(m_Window);

	m_Window->Open();

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

	 unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer::Create(vertices, sizeof(vertices));
	IndexBuffer::Create(indices, sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!m_Window->ShouldClose()) {
		glfwPollEvents();

		m_Window->Clear(0.0f, 0.0f, 1.0f, 1.0f);

  		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_Window->SwapBuffers();
	}

	delete m_Renderer;
	delete m_Window;

	return 0;
}
