#include "Common/UUID.hpp"

namespace BetterThanNothing {
	std::random_device UUID::s_RandomDevice = std::random_device();
	std::mt19937 UUID::s_TwisterEngine = std::mt19937(UUID::s_RandomDevice());
	std::uniform_int_distribution<uint64_t>	UUID::s_Distribution;

	UUID::UUID(): m_UUID(0) {};
	UUID::UUID(const uint64_t& UUID): m_UUID(UUID) {}

	UUID::operator uint64_t() const {
		return m_UUID;
	}

	UUID UUID::RandomUUID() {
		UUID uuid;
		uuid.m_UUID = s_Distribution(s_TwisterEngine);
		return uuid;
	}
};
