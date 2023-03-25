/*
 * File: UUID.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 10:06:41 pm
 * Last Modified: Saturday, 25th March 2023 10:06:42 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Core/UUID.h"

std::random_device UUID::s_RandomDevice = std::random_device();
std::mt19937 UUID::s_TwisterEngine = std::mt19937(UUID::s_RandomDevice());

UUID::UUID(void) {
	std::uniform_int_distribution<uint32_t> distribution(0, 15);

	const char *v = "0123456789abcdef";

	for (uint32_t index = 0; index < 32U; index++) {
		m_Values[index] = v[distribution(s_TwisterEngine)];
	}
}

UUID::UUID(const std::string& value) {
	for (uint32_t index = 0; index < 32U; index++) {
		if (value[index] != '-') {
			m_Values[index] = value[index];
		}
	}
}

std::ostream& operator<<(std::ostream& os, const UUID& uuid) {
	const bool dash[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (uint32_t index = 0; index < 32U; index++) {
		if (dash[index]) { os << '-'; }
		os << uuid.m_Values[index];
	}
	return os;
}
