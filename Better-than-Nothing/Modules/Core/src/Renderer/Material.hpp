#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief A material
	 */
	struct Material
	{
		/**
		 * @brief The material ambient color
		 */
		alignas(16) glm::vec3 ambient;

		/**
		 * @brief The material diffuse color
		 */
		alignas(16) glm::vec3 diffuse;

		/**
		 * @brief The material specular color
		 */
		alignas(16) glm::vec3 specular;

		/**
		 * @brief The material shininess
		 */
		alignas(4) float shininess;
	};
};
