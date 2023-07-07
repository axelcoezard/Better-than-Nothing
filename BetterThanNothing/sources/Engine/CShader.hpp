#pragma once

#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace BetterThanNothing {
	class CShader {
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
			uint32_t m_Shaders[2]{};
		};

	public:
		CShader();
		~CShader();

		void	AddTextSource(uint32_t type, const std::string& source);
		void	Compile();

		void	Bind() const;
		void	UnBind() const;

		void	BindAttribLocation(uint32_t position, const std::string& name) const;
		int		GetUniformLocation(const std::string& name) const;
		int		GetAttribLocation(const std::string& name) const;

		void	SetBool(const std::string& name, bool value) const;
		void	SetInt(const std::string& name, int value) const;
		void	SetFloat(const std::string& name, float value) const;
		void	SetPointer(const std::string& name, GLint size, GLsizei stride, const void* pointer) const;
	};
};
