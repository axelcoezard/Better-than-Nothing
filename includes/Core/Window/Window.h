/*
 * File: Window.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 7:29:47 pm
 * Last Modified: Tuesday, 7th March 2023 7:30:16 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <string>
#include <string_view>
#include <functional>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Events/EventDispatcher.h"
#include "Events/Event.h"
#include "Events/WindowCloseEvent.h"

struct WindowBuilder;

struct Window {
	private:
		GLFWwindow* m_Window;

		std::string m_title;
		uint32_t m_width, m_height;
		std::function<void(EventDispatcher*, Event*)> m_eventCallback;
	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window(void);

		void Open(void);
		void Close(void);

		bool ShouldClose(void);
		void SwapBuffers(void);
		void Clear(float red, float green, float blue, float alpha);

		void SetEventCallback(std::function<void(EventDispatcher*, Event*)> eventcallback);

		static WindowBuilder* GetBuilder(void);
};
