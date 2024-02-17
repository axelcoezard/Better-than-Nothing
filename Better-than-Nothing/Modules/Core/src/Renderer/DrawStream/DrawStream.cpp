#include "Renderer/DrawStream/DrawStream.hpp"
#include "Renderer/Pipeline.hpp"

namespace BetterThanNothing
{
	DrawStreamBuilder::DrawStreamBuilder(u32 capacity)
	{
		m_Size = 0;
	}

	DrawStreamBuilder::~DrawStreamBuilder()
	{
		m_PipelinesByIndex.clear();
		m_DrawPacketsPerPipeline.clear();
	}

	void DrawStreamBuilder::Draw(DrawPacket drawPacket)
	{
		if (m_Size == m_Capacity)
		{
			throw std::runtime_error("DrawStreamBuilder: no more space in draw stream");
		}

		Pipeline* pipeline = static_cast<Pipeline*>(drawPacket.pipeline);

		if (m_DrawPacketsPerPipeline.find(pipeline->GetId()) == m_DrawPacketsPerPipeline.end())
		{
			m_DrawPacketsPerPipeline.insert(std::pair<std::string, std::vector<DrawPacket>>(pipeline->GetId(), std::vector<DrawPacket>()));
			m_PipelinesByIndex.push_back(pipeline);
		}

		m_DrawPacketsPerPipeline.at(pipeline->GetId()).push_back(drawPacket);

		m_Size++;
	}

	std::vector<DrawStream>& DrawStreamBuilder::GetStreams()
	{
		u32 pipelineCount = m_PipelinesByIndex.size();

		std::vector<DrawStream> drawStream(pipelineCount);
		std::memset(drawStream.data(), 0, pipelineCount * sizeof(DrawStream));

		for (u32 i = 0; i < pipelineCount; i++)
		{
			DrawStream& currentStream = drawStream.at(i);
			Pipeline* currentPipeline = m_PipelinesByIndex[i];

			std::vector<DrawPacket>& currentPackets = m_DrawPacketsPerPipeline[currentPipeline->GetId()];

			currentStream.size = currentPackets.size();
			currentStream.pipeline = currentPipeline;
			currentStream.globalVertexCount = 0;
			currentStream.globalIndicesCount = 0;

			for (u32 j = 0; j < currentStream.size; j++)
			{
				currentStream.textures.push_back(currentPackets[j].texture);
				currentStream.models.push_back(currentPackets[j].model);
				currentStream.globalVertexCount += currentPackets[j].vertexCount;
				currentStream.globalIndicesCount += currentPackets[j].indicesCount;


			}

			//currentStream.globalVertexBuffer = globalVertexBuffer;
			//currentStream.globalIndexBuffer = globalIndexBuffer;
		}

		return drawStream;
	}
};
