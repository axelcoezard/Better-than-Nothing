#pragma once

#include <iostream>

namespace BetterThanNothing {
	class CTexture {
	private:
		uint32_t		m_Id;

		int				m_Width;
		int				m_Height;
		int				m_Channels;
		int				m_Format;

		unsigned char*	m_Data = nullptr;
	public:
		explicit CTexture();
		explicit CTexture(const std::string& fileName);
		~CTexture();

		void Bind(int position) const;
		void UnBind() const;
	};
};
