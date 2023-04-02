#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

template<uint32_t T>
class Buffer {
private:
	uint32_t	m_Id;
	void*		m_Data;
	uint32_t	m_DataSize;
public:
	explicit Buffer(void* data, uint32_t dataSize)
		: m_Id(0), m_Data(data), m_DataSize(dataSize) {
		glCreateBuffers(1, &m_Id);
		glBindBuffer(T, m_Id);
		glBufferData(T, m_DataSize, m_Data, GL_STATIC_DRAW);
	}

	~Buffer() { glDeleteBuffers(1, &m_Id); }

	void Bind() const { glBindBuffer(T, m_Id); }
	void UnBind() const { glBindBuffer(T, 0); }

	static Buffer<T>* Create(void* data, uint32_t dataSize) {
		return new Buffer<T>(data, dataSize);
	}
};

using VertexBuffer = Buffer<GL_ARRAY_BUFFER>;
using IndexBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
