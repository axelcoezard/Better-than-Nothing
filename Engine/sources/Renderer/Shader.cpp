/*
 * File: Shader.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 8:48:31 pm
 * Last Modified: Saturday, 25th March 2023 8:48:32 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Renderer/Shader.h"

Shader::Shader(void): m_Compiled(false) {}
Shader::~Shader(void) {}

void Shader::AddTextSource(uint32_t type, const std::string& source) {
	const char* c_str = source.c_str();
	unsigned int id;

	switch (type)
	{
		case Shader::VERTEX:
			id = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Shader::FRAGMENT:
			id = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			throw std::runtime_error("Unknown shader type");
	}

	glShaderSource(id, 1, &c_str, NULL);
	glCompileShader(id);

	m_Shaders[type] = id;
}

void Shader::Compile(void) {
	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);
	glLinkProgram(m_Program);

	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
	m_Compiled = true;
}

void Shader::Bind(void) {
	glUseProgram(m_Program);
}

void Shader::UnBind(void) {
	glUseProgram(0);
}
