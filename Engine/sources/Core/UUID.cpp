#include "Core/UUID.hpp"

std::random_device UUID::s_RandomDevice = std::random_device();
std::mt19937 UUID::s_TwisterEngine = std::mt19937(UUID::s_RandomDevice());
std::uniform_int_distribution<uint64_t>	UUID::s_Distribution;

UUID::UUID(void) = default;
UUID::UUID(const uint64_t& UUID): m_UUID(UUID){}

UUID::operator uint64_t(void) const {
	return m_UUID;
}

UUID UUID::RandomUUID(void) {
	UUID uuid;
	uuid.m_UUID = s_Distribution(s_TwisterEngine);
	return uuid;
}
