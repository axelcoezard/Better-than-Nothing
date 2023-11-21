#pragma once

namespace BetterThanNothing
{
	struct DirectionalLight
	{
		alignas(16) glm::vec3 color;

		alignas(4) float ambient;
		alignas(4) float diffuse;
		alignas(4) float specular;

		alignas(16) glm::vec3 direction;
	};

	struct PointLight
	{
		alignas(16) glm::vec3 color;

		alignas(4) float ambient;
		alignas(4) float diffuse;
		alignas(4) float specular;

		alignas(16) glm::vec3 position;

		alignas(4) float constant;
		alignas(4) float linear;
		alignas(4) float quadratic;
	};
};
