/*
 * File: Renderer.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 1:21:53 pm
 * Last Modified: Thursday, 9th March 2023 1:22:05 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>

#include "Core/Renderer.h"
#include "Core/Render/FrameBufferObject.h"
#include "Core/Window.h"

Renderer::Renderer(Window* window) {
	m_Window = window;
#if ENGINE_EDITOR_MODE
	m_fbo = new FrameBufferObject();
#endif
}

Renderer::~Renderer(void) {
#if ENGINE_EDITOR_MODE
	delete m_fbo;
#endif
}


void Renderer::Update(void) {

}


void Renderer::Render(void) {
#if ENGINE_EDITOR_MODE
	m_fbo->Bind();
#endif

	// Render all the stuff

#if ENGINE_EDITOR_MODE
	//m_fbo->UnBind();
	// Bind fbo texture to ImGui if in Editor mode
#endif
}
