#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The global uniforms
	 */
	struct GlobalUniforms
	{
		/**
		 * @brief The model matrix
		 */
		alignas(16) glm::mat4	model;

		/**
		 * @brief The camera view matrix
		 */
		alignas(16) glm::mat4	view;

		/**
		 * @brief The camera projection matrix
		 */
		alignas(16) glm::mat4	projection;
	};
};
