/*
 * File: Shader.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 8:43:12 pm
 * Last Modified: Saturday, 25th March 2023 8:43:13 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Shader {
public:
	static const uint32_t VERTEX = 0;
	static const uint32_t FRAGMENT = 1;

private:
	uint32_t	m_Program;
	bool		m_Compiled;

	union {
		struct {
			uint32_t m_VertexShader;
			uint32_t m_FragmentShader;
		};
		uint32_t m_Shaders[2];
	};

public:
	Shader(void);
	~Shader(void);

	void AddTextSource(uint32_t type, const std::string& source);
	void Compile(void);

	void Bind(void);
	void UnBind(void);
};
