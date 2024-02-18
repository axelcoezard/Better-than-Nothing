#include "Renderer/DrawStream/DrawStream.hpp"
#include "Renderer/Pipeline.hpp"

namespace BetterThanNothing
{
	DrawStreamBuilder::DrawStreamBuilder()
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
		Pipeline* pipeline = static_cast<Pipeline*>(drawPacket.pipeline);

		if (m_DrawPacketsPerPipeline.find(pipeline->GetId()) == m_DrawPacketsPerPipeline.end())
		{
			m_DrawPacketsPerPipeline.insert(std::pair<std::string, std::vector<DrawPacket>>(pipeline->GetId(), std::vector<DrawPacket>()));
			m_PipelinesByIndex.push_back(pipeline);
		}

		m_DrawPacketsPerPipeline.at(pipeline->GetId()).push_back(drawPacket);

		m_Size++;
	}

	std::vector<DrawStream> DrawStreamBuilder::GetStreams()
	{
		u32 pipelineCount = m_PipelinesByIndex.size();

		std::vector<DrawStream> drawStream(pipelineCount);
		//std::memset(drawStream.data(), 0, pipelineCount * sizeof(DrawStream));

		for (u32 i = 0; i < pipelineCount; i++)
		{
			DrawStream& currentStream = drawStream.at(i);
			Pipeline* currentPipeline = m_PipelinesByIndex[i];

			std::vector<DrawPacket>& currentPackets = m_DrawPacketsPerPipeline[currentPipeline->GetId()];

			currentStream.size = currentPackets.size();
			currentStream.pipeline = currentPipeline;
			currentStream.vertexCount = 0;
			currentStream.indicesCount = 0;

			for (u32 j = 0; j < currentStream.size; j++)
			{
				DrawPacket& currentPacket = currentPackets[j];

				currentStream.textures.push_back(currentPacket.texture);
				currentStream.models.push_back(currentPacket.model);

				currentStream.vertexBuffers.push_back(currentPacket.vertexBuffer.m_Buffer);
				currentStream.vertexOffsets.push_back(currentStream.vertexCount);
				currentStream.vertexCount += currentPacket.vertexCount;

				currentStream.indexBuffers.push_back(currentPacket.indexBuffer);
				currentStream.indexOffsets.push_back(currentStream.indicesCount);
				currentStream.indicesCount += currentPacket.indicesCount;
			}
		}

		return drawStream;
	}
};
