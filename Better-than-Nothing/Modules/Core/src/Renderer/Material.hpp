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
		alignas(4) float ambient;

		/**
		 * @brief The material diffuse color
		 */
		alignas(4) float diffuse;

		/**
		 * @brief The material specular color
		 */
		alignas(4) float specular;

		/**
		 * @brief The material shininess
		 */
		alignas(4) float shininess;
	};
};
