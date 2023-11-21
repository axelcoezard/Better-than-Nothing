#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	ConfigManager::ConfigManager(const std::string& basePath)
	{
		m_BasePath = basePath;
	}

	ConfigManager::~ConfigManager()
	{
		for (auto& reader : m_Readers) {
			delete reader.second;
		}
	}

	ConfigReader& ConfigManager::Read(const std::string& path)
	{
		if (m_Readers.find(path) == m_Readers.end()) {
			ConfigReader reader = new INIReader(m_BasePath + path);

			if (reader->ParseError() < 0) {
				throw std::runtime_error("Can't load config file: '" + path + "'");
			}

			m_Readers[path] = reader;
		}
		return m_Readers[path];
	}
};
