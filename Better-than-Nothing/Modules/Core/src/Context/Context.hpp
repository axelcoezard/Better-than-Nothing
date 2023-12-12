#pragma once

namespace BetterThanNothing
{
	class ConfigManager;

	class Window;
	class Device;

	struct Context
	{
		ConfigManager* configManager;
		Window* window;
		Device* device;
	};
};
