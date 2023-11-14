#include "Renderer/DrawStream.hpp"

namespace BetterThanNothing
{
		DrawStreamBuilder::DrawStreamBuilder(u32 capacity)
		{
			m_Size = 0;
			m_Capacity = capacity;
			m_DrawPackets.reserve(capacity);
		}

		DrawStreamBuilder::~DrawStreamBuilder()
		{
			m_DrawPackets.clear();
		}

		void DrawStreamBuilder::Draw(DrawPacket drawPacket)
		{
			if (m_Size == m_Capacity)
			{
				throw std::runtime_error("DrawStreamBuilder: no more space in draw stream");
			}

			m_DrawPackets.push_back(drawPacket);
			m_Size++;
		}

		DrawStream* DrawStreamBuilder::GetStream()
		{
			DrawStream* drawStream = new DrawStream();
			drawStream->m_Size = m_Size;
			drawStream->m_DrawPackets = new DrawPacket[m_Size];

			for (u32 i = 0; i < m_Size; i++) {
				drawStream->m_DrawPackets[i] = m_DrawPackets[i];
			}

			return drawStream;
		}
};
