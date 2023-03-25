/*
 * File: UUID.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 10:02:18 pm
 * Last Modified: Saturday, 25th March 2023 10:02:18 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <random>
#include <iostream>
#include <sstream>

class UUID {
private:
	unsigned char									m_UUID;

	static std::random_device						s_RandomDevice;
	static std::mt19937								s_TwisterEngine;
	static std::uniform_int_distribution<uint64_t>	s_Distribution;

public:
	UUID(void);
	UUID(const uint64_t& value);

	operator uint64_t(void) const;

	static UUID RandomUUID(void);
};
