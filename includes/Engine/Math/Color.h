/*
 * File: Color.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 11:37:23 am
 * Last Modified: Wednesday, 8th March 2023 11:37:24 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

struct Color {
	protected:
		union {
			struct {
				unsigned char m_red;
				unsigned char m_green;
				unsigned char m_blue;
				unsigned char m_alpha;
			};
			unsigned int m_rgba;
			unsigned char m_colors[4];
		};

	public:
		Color(void);
		Color(unsigned int rgba);
		Color(unsigned char red, unsigned char green, unsigned char blue);
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

		Color& SetRed(unsigned char red);
		Color& SetGreen(unsigned char green);
		Color& SetBlue(unsigned char blue);
		Color& SetAlpha(unsigned char alpha);

		float operator[](unsigned int index) const;
		bool operator==(const Color& b) const;
		bool operator!=(const Color& b) const;
};
