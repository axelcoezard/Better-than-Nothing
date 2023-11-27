#pragma once

#include "Ressources/Model.hpp"
#include "Ressources/Texture.hpp"

namespace BetterThanNothing
{
	struct ModelComponent
	{
		/**
		 * @brief The model of the entity.
		 */
		Model* model;

		/**
		 * @brief The texture of the entity.
		 */
		Texture* texture;
	};
};
