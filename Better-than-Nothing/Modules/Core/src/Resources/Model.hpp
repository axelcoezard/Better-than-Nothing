#pragma once

#include "Renderer/Buffer.hpp"
#include "Renderer/Vertex.hpp"

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
		 * @brief The vertices data of the model
		 */
		std::vector<Vertex> vertices;

		/**
		 * @brief The vertices buffer of the model
		 */
		Buffer vertexBuffer;

		/**
		 * @brief The number of vertices
		 */
		u32 vertexCount;

		/**
		 * @brief The indices data of the model
		 */
		std::vector<u32> indices;

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
