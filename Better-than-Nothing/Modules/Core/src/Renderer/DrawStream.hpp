#pragma once

namespace BetterThanNothing
{
	struct DrawPacket
	{
		void*					m_Texture;
		VkBuffer				m_VertexBuffer;
		VkBuffer				m_IndexBuffer;
	};

	struct DrawStream
	{
		u32						m_Size;
		DrawPacket*				m_DrawPackets;
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
