#pragma once

namespace BetterThanNothing
{
	class Device;
	class Buffer;

	template <typename T>
	class ResourcePool
	{
	protected:
		std::string							m_BasePath;
		std::unordered_map<std::string, T*>	m_Resources;
	public:
									ResourcePool(const std::string& basePath): m_BasePath(basePath) {}
		virtual						~ResourcePool() {}

		virtual T*					GetResource(const std::string& filePath) = 0;
	};
};
