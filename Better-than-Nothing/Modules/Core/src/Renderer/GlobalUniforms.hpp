#pragma once

namespace BetterThanNothing
{
	struct GlobalUniforms
	{
		alignas(16) glm::mat4	model;
		alignas(16) glm::mat4	view;
		alignas(16) glm::mat4	projection;
	};
};
