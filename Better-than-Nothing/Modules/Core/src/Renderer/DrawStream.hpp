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
	 * @brief A DrawStream is a collection of DrawPackets.
	 */
	struct DrawStream
	{
		/**
		 * @brief The size of the DrawStream.
		 */
		u32 size;

		/**
		 * @brief The DrawPackets.
		 */
		DrawPacket* drawPackets;
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
		 * @brief The DrawPackets.
		 */
		std::vector<DrawPacket> m_DrawPackets;

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
		void Draw(DrawPacket drawPacket) ;

		/**
		 * @brief Build the DrawStream.
		 * @return A pointer to the new DrawStream.
		 * @note The DrawPackets are sorted by pipeline while building the DrawStream.
		 */
		DrawStream* GetStream();
	};
};
