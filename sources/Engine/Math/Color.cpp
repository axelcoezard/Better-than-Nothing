/*
 * File: Color.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 1:49:14 pm
 * Last Modified: Wednesday, 8th March 2023 1:49:15 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <stdexcept>
#include "Math/Color.h"

Color::Color(void): m_rgba(0xFFFFFFFF) {}
Color::Color(unsigned int rgba) : m_rgba(rgba) {}

Color::Color(unsigned char red, unsigned char green, unsigned char blue)
	: m_red(red), m_green(green), m_blue(blue), m_alpha(255) {}

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	: m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}

Color& Color::SetRed(unsigned char red) {
	m_red = red;
	return *this;
}

Color& Color::SetGreen(unsigned char green) {
	m_green = green;
	return *this;
}

Color& Color::SetBlue(unsigned char blue) {
	m_blue = blue;
	return *this;
}

Color& Color::SetAlpha(unsigned char alpha) {
	m_alpha = alpha;
	return *this;
}

float Color::operator[](unsigned int index) const {
	if (index > 3) {
		throw new std::runtime_error("Color index out of bounds exception");
	}
	return static_cast<float>(m_colors[index]) / 255.0f;
}

bool Color::operator==(const Color& rhs) const {
	return m_red == rhs.m_red && m_green == rhs.m_green && m_blue == rhs.m_blue && m_alpha == rhs.m_alpha;
}

bool Color::operator!=(const Color& rhs) const {
	return m_red != rhs.m_red || m_green != rhs.m_green || m_blue != rhs.m_blue || m_alpha != rhs.m_alpha;
}
