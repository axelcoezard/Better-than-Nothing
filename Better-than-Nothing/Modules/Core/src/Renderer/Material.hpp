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
		 * @brief The material name
		 */
		std::string name;

		/**
		 * @brief The material ambient color
		 */
		glm::vec3 ambient;

		/**
		 * @brief The material diffuse color
		 */
		glm::vec3 diffuse;

		/**
		 * @brief The material specular color
		 */
		glm::vec3 specular;

		/**
		 * @brief The material shininess
		 */
		float shininess;
	};
};
