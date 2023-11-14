#pragma once

namespace BetterThanNothing
{
	struct DrawPacket
	{
		void*					pipeline;
		void*					texture;

		VkBuffer				vertexBuffer;
		VkBuffer				indexBuffer;
		u32						indicesCount;

		glm::mat4				model;
	};

	struct DrawStream
	{
		u32						size;
		DrawPacket*				drawPackets;
	};

	class DrawStreamBuilder
	{
	private:
		u32						m_Size;
		u32						m_Capacity;
		std::vector<DrawPacket> m_DrawPackets;

	public:
		DrawStreamBuilder(u32 capacity);
		~DrawStreamBuilder();

		void Draw(DrawPacket drawPacket);
		DrawStream* GetStream();
	};
};
