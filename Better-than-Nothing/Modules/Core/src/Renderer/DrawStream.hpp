#pragma once

namespace BetterThanNothing
{
	class Texture;
	struct DrawPacket
	{
		void*					m_pPipeline;
		void*					m_pTexture;

		VkBuffer				m_VertexBuffer;
		VkBuffer				m_IndexBuffer;
		u32						m_IndicesCount;

		glm::mat4				m_Model;
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
