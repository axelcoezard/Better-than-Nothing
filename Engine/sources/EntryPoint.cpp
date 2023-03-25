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
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Audio/AudioSystem.h"

static Window* m_Window;
static Renderer* m_Renderer;
static AudioSystem* m_AudioSystem;

int main(void) {
	m_Window = new Window("better than nothing", 720, 720);
	//m_Window->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));
	m_Window->Open();

	m_Renderer = new Renderer(m_Window);
	m_AudioSystem = new AudioSystem();

	Shader shader;
	shader.AddTextSource(Shader::VERTEX, "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0");
	shader.AddTextSource(Shader::FRAGMENT, "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0");

	shader.Compile();

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

	m_AudioSystem->Initialize();
	unsigned int buffer = m_AudioSystem->LoadSound("/home/acoezard/lab/better-than-nothing/fizzy.wav");
	m_AudioSystem->PlaySound(buffer);

	while (!m_Window->ShouldClose()) {
		glfwPollEvents();

		m_Window->Clear(0.0f, 0.0f, 1.0f, 1.0f);

		shader.Bind();
		glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		shader.UnBind();

		m_Window->SwapBuffers();
	}

	m_AudioSystem->Shutdown();

	delete m_AudioSystem;
	delete m_Renderer;
	delete m_Window;

	return 0;
}
