/*
 * File: Engine.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 1:28:16 pm
 * Last Modified: Saturday, 11th March 2023 1:28:17 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Core/EngineApp.h"

EngineApp::EngineApp(std::string_view title, uint32_t width, uint32_t height) {
	m_Window = new Window(title, width, height);
	m_Window->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));
	m_Renderer = new Renderer(m_Window);
}

void EngineApp::Run(void) {
	m_Window->Open();
	this->OnEnable();

	while (!m_Window->ShouldClose()) {
		glfwPollEvents();

		this->OnUpdate();
		m_Window->Clear(0.0f, 0.0f, 1.0f, 1.0f);
		this->OnRender(m_Renderer);

		m_Window->SwapBuffers();
	}
	this->OnDisable();

	delete m_Renderer;
	delete m_Window;
}
