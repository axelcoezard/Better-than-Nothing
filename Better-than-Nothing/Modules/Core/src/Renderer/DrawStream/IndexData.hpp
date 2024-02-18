#pragma once

#include "Renderer/Buffer.hpp"

namespace BetterThanNothing
{
	struct IndexData
	{
		alignas(4) u32 indexCount;

		std::vector<Buffer> indices;
	};
};
