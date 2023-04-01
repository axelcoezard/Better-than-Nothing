#pragma once

#include <iostream>

class Texture {
private:
	uint32_t		m_Id;

	int				m_Width;
	int				m_Height;
	int				m_Channels;
	int				m_Format;

	unsigned char*	m_Data = nullptr;
public:
	Texture(void);
	Texture(const std::string& fileName);
	~Texture(void);

	void Bind(int position);
	void UnBind(void);
};
