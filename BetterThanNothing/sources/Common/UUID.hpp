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
	UUID();
	explicit UUID(const uint64_t& value);

	explicit operator uint64_t() const;

	static UUID RandomUUID();
};
