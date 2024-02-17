#pragma once

#include "Renderer/Buffer.hpp"

namespace BetterThanNothing
{
	struct VertexData
	{
		alignas(4) u32 vertexCount;

		std::vector<Buffer> vertices;
	};
};
