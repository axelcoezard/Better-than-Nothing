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

#include "Core/GarbageCollector/GCObject.h"
#include "Events/Event.h"
#include "Events/WindowCloseEvent.h"

struct WindowBuilder;

struct Window: public GCObject {
	private:
		GLFWwindow* m_window;

		struct WindowData {
			std::string m_title;
			uint32_t m_width, m_height;
			std::function<void(Event*)> m_eventCallback;
		} m_data;
	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window(void);

		void Open(void);
		bool ShouldClose(void);
		void Clear(void);
		void SwapBuffers(void);
		void Close(void);

		void onEvent(Event* event);
		bool onWindowCloseEvent(WindowCloseEvent* event);

		void SetEventCallback(std::function<void(Event*)> eventcallback);

		static WindowBuilder* GetBuilder(void);
};
