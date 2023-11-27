#pragma once

namespace BetterThanNothing
{
	struct TransformComponent
	{
		/**
		 * @brief The position of the entity.
		 */
		glm::vec3 position;

		/**
		 * @brief The rotation of the entity in degrees.
		 */
		glm::vec3 rotation;

		/**
		 * @brief The scale of the entity.
		 */
		glm::vec3 scale;

		static glm::mat4 GetModelMatrix(TransformComponent& transformComponent)
		{
			glm::mat4 model(1.0f);

			model = glm::translate(model, transformComponent.position);

			model = glm::rotate(model, glm::radians(transformComponent.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(transformComponent.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(transformComponent.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			model = glm::scale(model, glm::vec3(transformComponent.scale));

			return model;
		}
	};
};
