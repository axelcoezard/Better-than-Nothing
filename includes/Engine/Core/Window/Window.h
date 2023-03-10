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

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/GarbageCollector/GCObject.h"

struct WindowBuilder;

struct Window: public GCObject {
	private:
		GLFWwindow* m_window;

		std::string m_title;
		uint32_t m_width;
		uint32_t m_height;

	public:
		Window(std::string_view title, uint32_t width, uint32_t height);
		~Window(void);

		bool ShouldClose(void);
		void Clear(void);
		void SwapBuffers(void);

		static WindowBuilder* GetBuilder(void);
};
