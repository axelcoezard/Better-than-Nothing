#pragma once

namespace BetterThanNothing
{
	class ConfigManager;

	class Window;
	class Device;

	struct Context
	{
		std::string name;

		ConfigManager* configManager;
		Window* window;
		Device* device;
	};
};
