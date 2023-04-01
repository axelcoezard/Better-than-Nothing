#include "Renderer/Shader.hpp"

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

void Shader::BindAttribLocation(uint32_t position, const std::string& name) const {
	glBindAttribLocation(m_Program, position, name.c_str());
}

int Shader::GetUniformLocation(const std::string& name) const {
	return glGetUniformLocation(m_Program, name.c_str());
}

int Shader::GetAttribLocation(const std::string& name) const {
	return glGetAttribLocation(m_Program, name.c_str());
}

void Shader::SetBool(const std::string& name, bool value) const {
	glUniform1i(GetUniformLocation(name), (int) value);
}

void Shader::SetInt(const std::string& name, int value) const {
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const {
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetPointer(const std::string& name, GLint size, GLsizei stride, const void* pointer) const {
	int location = GetAttribLocation(name);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(location);
}
