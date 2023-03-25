/*
 * File: Window.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:29:47 pm
 * Last Modified: Tuesday, 7th March 2023 7:30:16 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */
#pragma once

#include <string>
#include <string_view>
#include <functional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Events/EventDispatcher.hpp"
#include "Events/Event.hpp"
#include "Events/WindowCloseEvent.hpp"

struct Window {
private:
	GLFWwindow*					m_Window;

	std::string					m_Title;
	uint32_t					m_Width, m_Height;
	std::function<void(Event*)>	m_eventCallback;
public:
	Window(std::string_view title, uint32_t width, uint32_t height);
	~Window(void);

	void Open(void);
	void Close(void);

	bool ShouldClose(void);
	void SwapBuffers(void);
	void Clear(float red, float green, float blue, float alpha);

	void SetEventCallback(std::function<void(Event*)> eventcallback);

	uint32_t GetWidth(void);
	uint32_t GetHeight(void);
};
