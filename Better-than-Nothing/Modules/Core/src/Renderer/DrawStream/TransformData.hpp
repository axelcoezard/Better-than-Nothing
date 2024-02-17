#pragma once

namespace BetterThanNothing
{
	struct TransformData
	{
		alignas(4) u32 modelCount;

		std::vector<glm::mat4> model;
	};
};
