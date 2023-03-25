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
	unsigned char m_Values[32];

	static std::random_device s_RandomDevice;
	static std::mt19937 s_TwisterEngine;

public:
	UUID(void);
	UUID(const std::string& value);

	friend std::ostream& operator<<(std::ostream& os, const UUID& m);
};

std::ostream& operator<<(std::ostream& os, const UUID& m);
