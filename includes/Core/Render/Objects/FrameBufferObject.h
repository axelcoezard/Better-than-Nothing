/*
 * File: FrameBufferObject.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Friday, 10th March 2023 1:40:50 pm
 * Last Modified: Friday, 10th March 2023 1:43:55 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Core/GarbageCollector/GCObject.h"

struct FrameBufferObject: public GCObject {
	private:
		unsigned int m_id;
		unsigned int m_texture;
	public:
		FrameBufferObject(void);
		~FrameBufferObject(void);

		void Bind(void);
		void UnBind(void);

		unsigned int GetTexture(int width, int height);
};
