/*
 * File: VertexArrayObject.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Friday, 10th March 2023 1:38:49 pm
 * Last Modified: Friday, 10th March 2023 3:13:28 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct VertexArrayObject {
	private:
		unsigned int m_Id;
	public:
		VertexArrayObject(void);
		~VertexArrayObject(void);

		void Bind(void);
		void UnBind(void);
};