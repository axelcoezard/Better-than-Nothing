#include "Engine/CTexture.hpp"

#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace BetterThanNothing {
	CTexture::CTexture()
		: m_Id(0), m_Width(0), m_Height(0), m_Channels(0), m_Format(0), m_Data(nullptr) {}

	CTexture::CTexture(const std::string& fileName)
		: m_Id(0), m_Width(0), m_Height(0), m_Channels(0)  {
		const char* c_str = fileName.c_str();

		stbi_set_flip_vertically_on_load(true);
		m_Data = stbi_load(c_str, &m_Width, &m_Height, &m_Channels, 0);

		if (m_Data == nullptr) {
			std::cerr << "Failed to load texture: " << fileName << std::endl;
		}

		m_Format = m_Channels > 3 ? GL_RGBA : GL_RGB;

		glGenTextures(1, &m_Id);
		Bind(-1);

		glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_Width, m_Height, 0, m_Format, GL_UNSIGNED_BYTE, m_Data);
		glGenerateMipmap(GL_TEXTURE_2D);

		UnBind();
	}

	CTexture::~CTexture() {
		if (m_Data != nullptr) {
			stbi_image_free(m_Data);
		}
	}

	void CTexture::Bind(int position) const {
		if (position != -1) {
			glActiveTexture(position);
		}
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}

	void CTexture::UnBind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};
