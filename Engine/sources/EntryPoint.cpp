#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture.hpp"
#include "Audio/AudioSystem.hpp"

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
		"layout (location = 1) in vec2 aTexture;\n"
		"out vec2 vTexture;\n"
		"void main() {\n"
		"   vTexture = aTexture;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0");
	shader.AddTextSource(Shader::FRAGMENT, "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 vTexture;\n"
		"uniform sampler2D Texture0;\n"
		"void main() {\n"
		"   FragColor = texture(Texture0, vTexture);\n"
		"}\0");

	Texture texture = Texture("/home/acoezard/lab/better-than-nothing/test.png");

	float vertices[] = {
		// positions        // texture
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer::Create(vertices, sizeof(vertices));

	shader.Compile();
	shader.SetPointer("aPos", 3, 5 * sizeof(float), (void*) (0 * sizeof(float)));
	shader.SetPointer("aTexture", 2, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	shader.Bind();

	IndexBuffer::Create(indices, sizeof(indices));

	glBindVertexArray(0);

	m_AudioSystem->Initialize();
	unsigned int buffer = m_AudioSystem->LoadSound("/home/acoezard/lab/better-than-nothing/fizzy.wav");
	m_AudioSystem->PlaySound(buffer);

	while (!m_Window->ShouldClose()) {
		glfwPollEvents();

		m_Window->Clear(0.0f, 0.0f, 1.0f, 1.0f);

		texture.Bind(GL_TEXTURE0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		m_Window->SwapBuffers();
	}

	shader.UnBind();
	texture.UnBind();

	m_AudioSystem->Shutdown();

	delete m_AudioSystem;
	delete m_Renderer;
	delete m_Window;

	return 0;
}
