/*
 * File: Texture.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Sunday, 26th March 2023 5:13:50 pm
 * Last Modified: Sunday, 26th March 2023 5:13:51 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Renderer/Texture.hpp"

#include "stb_image.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Texture::Texture(void) = default;
Texture::Texture(const std::string& fileName) {
	m_Data = stbi_load(fileName.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (m_Data != nullptr) {
		std::cerr << "Failed to load texture: " << fileName << std::endl;
	}

	glGenTextures(1, &m_Id);
	Bind();

	unsigned int format = m_Channels > 3 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	UnBind();
}

Texture::~Texture(void) {
	if (m_Data != nullptr) {
		stbi_image_free(m_Data);
	}
}

void Texture::Bind(void) {
	glBindTexture(GL_TEXTURE_2D, m_Id);
}

void Texture::UnBind(void) {
	glBindTexture(GL_TEXTURE_2D, 0);
}
