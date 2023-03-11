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
	m_window = Window::GetBuilder()
		->WithTitle(title)
		->WithSize(width, height)
		->Build();
	m_window->SetEventCallback(BIND_EVENT_LISTENER(OnEvent));
	m_renderer = new Renderer(m_window);
}

void EngineApp::Run(void) {
	m_window->Open();
	this->OnEnable();
	while (!m_window->ShouldClose()) {
		glfwPollEvents();

		m_renderer->Update();
		this->OnUpdate();

		m_window->Clear(0.0f, 0.0f, 1.0f, 1.0f);

		m_renderer->Render();
		this->OnRender();

		m_window->SwapBuffers();
	}
	this->OnDisable();
}
