#pragma once

#include <string>
#include <string_view>
#include <functional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Events/CEventDispatcher.hpp"
#include "Events/CEvent.hpp"
#include "Events/CWindowCloseEvent.hpp"

struct CWindow {
private:
	GLFWwindow*					m_pWindow;

	std::string					m_Title;
	uint32_t					m_Width, m_Height;
	std::function<void(Event*)>	m_eventCallback;
public:
	CWindow(std::string_view title, uint32_t width, uint32_t height);
	~CWindow();

	void Open();
	void Close();

	bool ShouldClose();
	void SwapBuffers();
	void Clear(float red, float green, float blue, float alpha);

	void SetEventCallback(std::function<void(CEvent*)>& eventcallback);

	uint32_t GetWidth();
	uint32_t GetHeight();
};
