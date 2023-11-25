#pragma once

#include "Renderer/Buffer.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief The model struct that contains all the data of a 3D model
	 */
	struct Model
	{
		/**
		 * @brief The file path of the model
		 */
		std::string filePath;

		/**
		 * @brief The vertices buffer of the model
		 */
		Buffer vertexBuffer;

		/**
		 * @brief The indices buffer of the model
		 */
		Buffer indexBuffer;

		/**
		 * @brief The number of indices
		 */
		u32 indexCount;
	};
};
