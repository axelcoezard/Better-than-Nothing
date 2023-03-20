/*
 * File: BehaviorCollector.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Thursday, 9th March 2023 1:18:31 pm
 * Last Modified: Thursday, 9th March 2023 1:18:36 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <vector>

#include "Core/Render/Objects/FrameBufferObject.h"

struct Window;

struct Renderer {
	private:
		Window* m_window;
#if ENGINE_EDITOR_MODE
		FrameBufferObject* m_fbo;
#endif
	public:
		Renderer(Window* window);
		~Renderer(void);

		void Update(void);
		void Render(void);
};
