/*
 * File: Texture.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Sunday, 26th March 2023 2:31:53 pm
 * Last Modified: Sunday, 26th March 2023 2:32:18 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <iostream>

class Texture {
private:
	uint32_t		m_Id;

	int				m_Width;
	int				m_Height;
	int				m_Channels;

	unsigned char*	m_Data = nullptr;
public:
	Texture(void);
	Texture(const std::string& fileName);
	~Texture(void);

	void Bind(void);
	void UnBind(void);
};