#pragma once

#include "Renderer/Material.hpp"

namespace BetterThanNothing
{
	struct MaterialData
	{
		alignas(4) u32 materialCount;

		std::vector<Material> materials;
	};
};
