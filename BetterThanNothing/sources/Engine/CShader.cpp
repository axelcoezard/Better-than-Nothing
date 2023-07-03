#include "Engine/Shader.hpp"

CShader::CShader()
	: m_Program(0), m_Compiled(false), m_VertexShader(0), m_FragmentShader(0) {}

CShader::~CShader() = default;

void CShader::AddTextSource(uint32_t type, const std::string& source) {
	const char* c_str = source.c_str();
	unsigned int id;

	switch (type)
	{
		case CShader::VERTEX:
			id = glCreateShader(GL_VERTEX_SHADER);
			break;
		case CShader::FRAGMENT:
			id = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			throw std::runtime_error("Unknown shader type");
	}

	glShaderSource(id, 1, &c_str, nullptr);
	glCompileShader(id);

	m_Shaders[type] = id;
}

void CShader::Compile() {
	m_Program = glCreateProgram();
	glAttachShader(m_Program, m_VertexShader);
	glAttachShader(m_Program, m_FragmentShader);
	glLinkProgram(m_Program);

	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
	m_Compiled = true;
}

void CShader::Bind() const {
	if (m_Compiled) {
		glUseProgram(m_Program);
	}
}

void CShader::UnBind() const {
	glUseProgram(0);
}

void CShader::BindAttribLocation(uint32_t position, const std::string& name) const {
	glBindAttribLocation(m_Program, position, name.c_str());
}

int CShader::GetUniformLocation(const std::string& name) const {
	return glGetUniformLocation(m_Program, name.c_str());
}

int CShader::GetAttribLocation(const std::string& name) const {
	return glGetAttribLocation(m_Program, name.c_str());
}

void CShader::SetBool(const std::string& name, bool value) const {
	glUniform1i(GetUniformLocation(name), (int) value);
}

void CShader::SetInt(const std::string& name, int value) const {
	glUniform1i(GetUniformLocation(name), value);
}

void CShader::SetFloat(const std::string& name, float value) const {
	glUniform1f(GetUniformLocation(name), value);
}

void CShader::SetPointer(const std::string& name, GLint size, GLsizei stride, const void* pointer) const {
	int location = GetAttribLocation(name);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(location);
}
