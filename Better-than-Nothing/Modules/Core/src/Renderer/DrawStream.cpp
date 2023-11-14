#include "Renderer/DrawStream.hpp"
#include "Renderer/Pipeline.hpp"

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
		// Sort the draw packets by pipeline
		std::sort(m_DrawPackets.begin(), m_DrawPackets.end(), [](const DrawPacket& a, const DrawPacket& b){
			auto pPipelineA = static_cast<Pipeline*>(a.m_pPipeline);
			auto pPipelineB = static_cast<Pipeline*>(b.m_pPipeline);

			return pPipelineA->GetId() < pPipelineB->GetId();
		});

		// Copy the draw packets sorted by pipeline into allocated memory
		DrawPacket* drawPackets = new DrawPacket[m_Size];
		std::copy(m_DrawPackets.begin(), m_DrawPackets.end(), drawPackets);

		// Create the draw stream using the sorted draw packets
		DrawStream* drawStream = new DrawStream();
		drawStream->m_Size = m_Size;
		drawStream->m_DrawPackets = drawPackets;
		return drawStream;
	}
};
