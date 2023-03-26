/*
 * File: Buffer.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 21st March 2023 10:04:53 pm
 * Last Modified: Tuesday, 21st March 2023 10:04:55 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */
#pragma once

#include <stdint.h>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

template<uint32_t __TYPE>
class Buffer {
private:
	uint32_t	m_Id;
	void*		m_Data;
	uint32_t	m_DataSize;
public:
	Buffer(void* data, uint32_t dataSize)
		: m_Data(data), m_DataSize(dataSize) {
		glCreateBuffers(1, &m_Id);
		glBindBuffer(__TYPE, m_Id);
		glBufferData(__TYPE, m_DataSize, m_Data, GL_STATIC_DRAW);
	}

	~Buffer(void) { glDeleteBuffers(1, &m_Id); }

	void Bind(void) const { glBindBuffer(__TYPE, m_Id); }
	void UnBind(void) const { glBindBuffer(__TYPE, 0); }

	static Buffer<__TYPE>* Create(void* data, uint32_t dataSize) {
		return new Buffer<__TYPE>(data, dataSize);
	}
};

using VertexBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
