#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Engine/CWindow.hpp"
#include "Engine/CBuffer.hpp"
#include "Engine/CShader.hpp"
#include "Engine/CTexture.hpp"
#include "AudioSystem/CAudioSystem.hpp"

using namespace BetterThanNothing;

static CWindow* m_pWindow;

int main(void) {
	m_pWindow = new CWindow("better than nothing", 720, 720);
	//m_pWindow->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));
	m_pWindow->Open();

	CShader shader;
	shader.AddTextSource(CShader::VERTEX, "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexture;\n"
		"out vec2 vTexture;\n"
		"void main() {\n"
		"   vTexture = aTexture;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0");
	shader.AddTextSource(CShader::FRAGMENT, "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 vTexture;\n"
		"uniform sampler2D Texture0;\n"
		"void main() {\n"
		"   FragColor = texture(Texture0, vTexture);\n"
		"}\0");

	CTexture texture = CTexture("/home/acoezard/lab/better-than-nothing/test.png");

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

	CVertexBuffer::Create(vertices, sizeof(vertices));

	shader.Compile();
	shader.SetPointer("aPos", 3, 5 * sizeof(float), (void*) (0 * sizeof(float)));
	shader.SetPointer("aTexture", 2, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	shader.Bind();

	CIndexBuffer::Create(indices, sizeof(indices));

	glBindVertexArray(0);

	CAudioSystem::Initialize();
	CAudioBuffer buffer = CAudioSystem::LoadSound("/home/acoezard/lab/better-than-nothing/fizzy.wav");
    CAudioSystem::PlaySound(buffer);

	while (!m_pWindow->ShouldClose()) {
		glfwPollEvents();

		m_pWindow->Clear(0.0f, 0.0f, 1.0f, 1.0f);

		texture.Bind(GL_TEXTURE0);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		m_pWindow->SwapBuffers();
	}

	shader.UnBind();
	texture.UnBind();

	CAudioSystem::Shutdown();

	delete m_pWindow;

	return 0;
}
