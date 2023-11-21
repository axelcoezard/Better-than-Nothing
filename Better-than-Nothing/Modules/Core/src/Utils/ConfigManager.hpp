#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief A typedef for INIReader
	 */
	typedef INIReader* ConfigReader;

	/**
	 * @brief A class to manage all config files
	 */
	class ConfigManager
	{
	private:

		/**
		 * @brief All ConfigReader for all config files
		 */
		std::map<std::string, ConfigReader> m_Readers;

		/**
		 * @brief The path to the config file
		 */
		std::string m_BasePath;

	public:

		/**
		 * @brief Construct a new ConfigManager object
		 * @param path The base path to the config file
		 */
		ConfigManager(const std::string& basePath);

		/**
		 * @brief Destroy the ConfigManager object
		 */
		~ConfigManager();

		/**
		 * @brief Get the INIReader object
		 * @param name The relative path of the config file
		 * @return ConfigReader& A pointer to a INIReader object
		 * @note Try to read the config file if it's not already loaded
		 */
		ConfigReader& Read(const std::string& path);
	};
};
