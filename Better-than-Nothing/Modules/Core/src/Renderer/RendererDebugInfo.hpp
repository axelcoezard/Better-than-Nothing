#pragma once

namespace BetterThanNothing
{
	struct RendererDebugInfo
	{
		std::string vendorName;
		std::string deviceName;
		std::string apiVersion;

		u32 frameCount;
		f32 frameTime;
		f32 deltaTime;

		u32 drawCalls;
		u32 totalDrawCalls;

		std::string sceneName;
		u32 sceneEntitiesCount;
	};
};
