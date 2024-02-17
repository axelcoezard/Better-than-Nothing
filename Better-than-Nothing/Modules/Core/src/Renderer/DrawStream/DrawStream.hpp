#pragma once

#include "Renderer/Buffer.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief A DrawPacket is a collection of data that is used to draw a single object.
	 */
	struct DrawPacket
	{
		/**
		 * @brief A pointer to a Pipeline.
		 */
		void* pipeline;

		/**
		 * @brief A pointer to a Texture.
		 */
		void* texture;

		/**
		 * @brief The vertex buffer.
		 */
		Buffer vertexBuffer;

		/**
		 * @brief The number of vertices.
		 */
		u32 vertexCount;

		/**
		 * @brief The index buffer.
		 */
		Buffer indexBuffer;

		/**
		 * @brief The number of indices.
		 */
		u32 indicesCount;

		/**
		 * @brief The model matrix.
		 */
		glm::mat4 model;
	};

	/**
	 * @brief A DrawStream is used to draw multiple objects at once.
	 */
	struct DrawStream
	{
		/**
		 * @brief The size of the DrawStream.
		 */
		u32 size;

		/**
		 * @brief The pipeline used to draw each model in the DrawStream.
		 */
		void* pipeline;

		/**
		 * @brief The textures used to draw each model in the DrawStream.
		 */
		std::vector<void*> textures;

		/**
		 * @brief The model matrices used to draw each model in the DrawStream.
		 */
		std::vector<glm::mat4> models;

		/**
		 * @brief The vertex buffer that contains all the vertices of each model in the DrawStream.
		 */
		Buffer globalVertexBuffer;

		/**
		 * @brief The number of vertices in the globalVertexBuffer.
		 */
		u32 globalVertexCount;

		/**
		 * @brief The index buffer that contains all the indices of each model in the DrawStream.
		 */
		Buffer globalIndexBuffer;

		/**
		 * @brief The number of indices in the globalIndexBuffer.
		 */
		u32 globalIndicesCount;
	};

	/**
	 * @brief A DrawStreamBuilder is used to build a DrawStream.
	 */
	class DrawStreamBuilder
	{
	private:
		/**
		 * @brief The size of the DrawStream.
		 */
		u32 m_Size;

		/**
		 * @brief The capacity of the DrawStream.
		 */
		u32 m_Capacity;

		/**
		 * @brief The DrawPackets for each pipeline.
		 * @note We use a vector of pairs to keep the order of the DrawPackets.
		 */
		std::map<std::string, std::vector<DrawPacket>> m_DrawPacketsPerPipeline;
		std::vector<Pipeline*> m_PipelinesByIndex;

	public:
		/**
		 * @brief Construct a new DrawStreamBuilder.
		 * @param capacity The maximum capacity of the DrawStream.
		 */
		DrawStreamBuilder(u32 capacity);

		/**
		 * @brief Destroy the DrawStreamBuilder and clear DrawPackets.
		 */
		~DrawStreamBuilder();

		/**
		 * @brief Add a DrawPacket to the DrawStream.
		 * @param drawPacket The DrawPacket to add.
		 */
		void Draw(DrawPacket drawPacket);

		/**
		 * @brief Build the DrawStream.
		 * @return A pointer to the new DrawStream.
		 * @note The DrawPackets are sorted by pipeline while building the DrawStream.
		 */
		std::vector<DrawStream>& GetStreams();

	private:

	};
};
