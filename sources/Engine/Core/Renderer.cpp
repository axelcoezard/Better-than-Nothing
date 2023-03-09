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
#include "Core/Behavior.h"

Renderer* Renderer::m_instance = nullptr;

Renderer::Renderer(void) {

}

Renderer::~Renderer(void) {
	m_behaviors.clear();
}

void Renderer::RegisterBehavior(Behavior* behavior) {
	m_behaviors.insert(behavior);
}

void Renderer::UnregisterBehavior(Behavior* behavior) {
	m_behaviors.erase(behavior);
}

void Renderer::Update(void) {

}


void Renderer::Render(void) {

}


Renderer* Renderer::Get(void) {
	if (m_instance == nullptr) {
		m_instance = new Renderer();
	}
	return m_instance;
}
