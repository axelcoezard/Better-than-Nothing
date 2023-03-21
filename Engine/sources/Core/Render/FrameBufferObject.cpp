/*
 * File: FrameBufferObject.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Friday, 10th March 2023 1:49:49 pm
 * Last Modified: Friday, 10th March 2023 1:49:51 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <stdexcept>
#include "Core/Render/FrameBufferObject.h"

FrameBufferObject::FrameBufferObject(void) {
	glGenFramebuffers(1, &m_Id);
}

FrameBufferObject::~FrameBufferObject(void) {
	glDeleteFramebuffers(1, &m_Id);
}

void FrameBufferObject::Bind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Cannot bind frame buffer");
}

void FrameBufferObject::UnBind(void) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int FrameBufferObject::GetTexture(int width, int height) {
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);
	return m_TextureId;
}
