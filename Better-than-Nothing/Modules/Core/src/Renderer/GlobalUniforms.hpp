#pragma once

#include "Scene/Light.hpp"
#include "Renderer/Material.hpp"

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
		alignas(16) glm::mat4 model;

		/**
		 * @brief The camera view matrix
		 */
		alignas(16) glm::mat4 view;

		/**
		 * @brief The camera projection matrix
		 */
		alignas(16) glm::mat4 projection;

		/**
		 * @brief The camera position
		 */
		alignas(16) glm::vec3 cameraPosition;

		/**
		 * @brief The material
		 */
		Material material;

		/**
		 * @brief The directional light
		 */
		DirectionalLight directionalLight;

		/**
		 * @brief The point lights
		 */
		std::vector<PointLight> pointLights;
	};
};
