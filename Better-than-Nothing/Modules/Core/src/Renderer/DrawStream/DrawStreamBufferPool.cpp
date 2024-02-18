#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	DrawStreamBufferPool::DrawStreamBufferPool(Device* device): m_Device(device)
	{

	}

	DrawStreamBufferPool::~DrawStreamBufferPool()
	{
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_Device->UnmapBuffer(m_GlobalData[i]);
			m_Device->DestroyBuffer(m_GlobalData[i]);
		}
		m_GlobalData.clear();

		for (u32 i = 0; i < m_MaterialData.size(); i++) {
			for (u32 j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
				m_Device->UnmapBuffer(m_MaterialData[i][j]);
				m_Device->DestroyBuffer(m_MaterialData[i][j]);
			}
		}
		m_MaterialData.clear();

		for (u32 i = 0; i < m_TransformData.size(); i++) {
			for (u32 j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
				m_Device->UnmapBuffer(m_TransformData[i][j]);
				m_Device->DestroyBuffer(m_TransformData[i][j]);
			}
		}
		m_TransformData.clear();

		for (u32 i = 0; i < m_VertexData.size(); i++) {
			for (u32 j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
				m_Device->UnmapBuffer(m_VertexData[i][j]);
				m_Device->DestroyBuffer(m_VertexData[i][j]);
			}
		}
		m_VertexData.clear();
	}

	void DrawStreamBufferPool::AllocateAllGlobalData()
	{
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_GlobalData.push_back(new Buffer());

			m_Device->CreateBuffer(
				m_GlobalData[i],
				sizeof(GlobalData),
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(m_GlobalData[i], 0, 0, &m_GlobalData[i]->m_Mapped);
		}
	}

	std::vector<Buffer*>& DrawStreamBufferPool::CreateMaterialData()
	{
		std::vector<Buffer*> buffers;
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			Buffer* buffer = new Buffer();

			m_Device->CreateBuffer(
				buffer,
				sizeof(MaterialData),
				VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(buffer, 0, 0, &buffer->m_Mapped);

			buffers.push_back(buffer);
		}

		m_MaterialData.push_back(buffers);

		return m_MaterialData.back();
	}

	std::vector<Buffer*>& DrawStreamBufferPool::CreateTransformData()
	{
		std::vector<Buffer*> buffers;
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			Buffer* buffer = new Buffer();

			m_Device->CreateBuffer(
				buffer,
				sizeof(TransformData),
				VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			m_Device->MapBuffer(buffer, 0, 0, &buffer->m_Mapped);

			buffers.push_back(buffer);
		}

		m_TransformData.push_back(buffers);

		return m_TransformData.back();
	}

	std::vector<Buffer*>& DrawStreamBufferPool::GetAllGlobalData()
	{
		return m_GlobalData;
	}

	GlobalData* DrawStreamBufferPool::GetGlobalData(u32 frame)
	{
		return static_cast<GlobalData*>(m_GlobalData[frame]->m_Mapped);
	}

	MaterialData* DrawStreamBufferPool::GetMaterialData(u32 frame, u32 index)
	{
		return static_cast<MaterialData*>(m_MaterialData[index][frame]->m_Mapped);
	}

	TransformData* DrawStreamBufferPool::GetTransformData(u32 frame, u32 index)
	{
		return static_cast<TransformData*>(m_TransformData[index][frame]->m_Mapped);
	}
};
