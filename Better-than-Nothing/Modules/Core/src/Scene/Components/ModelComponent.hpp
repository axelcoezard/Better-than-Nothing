#pragma once

#include "Resources/Model.hpp"
#include "Resources/Texture.hpp"

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
