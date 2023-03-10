/*
 * File: WindowBuilder.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:43:21 pm
 * Last Modified: Tuesday, 7th March 2023 7:43:29 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Core/Window/WindowBuilder.h"
#include "Core/Window/Window.h"

WindowBuilder* WindowBuilder::WithTitle(std::string_view title) {
	m_title = title;
	return this;
}

WindowBuilder* WindowBuilder::WithSize(uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;
	return this;
}

Window* WindowBuilder::Build(void) const {
	return new Window(m_title, m_width, m_height);
}
