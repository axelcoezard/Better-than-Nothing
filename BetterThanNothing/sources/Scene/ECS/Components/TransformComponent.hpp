#pragma once

#include "Scene/ECS/Component.hpp"

namespace BetterThanNothing
{
	struct TransformComponent: public Component
	{
		glm::vec3	position;
		glm::vec3	rotation;
		float		scale;

		COMPONENT_NAME(TransformComponent)
	};
};
