/*
 * File: VertexBufferObject.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Friday, 10th March 2023 1:38:54 pm
 * Last Modified: Friday, 10th March 2023 3:13:44 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct VertexBufferObject {
	private:
		unsigned int m_id;
	public:
		VertexBufferObject(void);
		~VertexBufferObject(void);
};
