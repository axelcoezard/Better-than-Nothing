#pragma once

#include "Renderer/Material.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief The global uniforms
	 */
	struct DynamicUniforms
	{
		/**
		 * @brief The model matrix
		 */
		alignas(16) glm::mat4 model;

		/**
		 * @brief The material
		 */
		Material material;
	};
};
