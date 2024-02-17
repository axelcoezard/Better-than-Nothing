#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;

	class GlobalData;
	class MaterialData;
	class TransformData;
	class VertexData;
	class IndexData;

	class DrawStreamBufferPool
	{
	private:
		Device* m_Device;

		std::vector<Buffer*> m_GlobalData; // 1 per frame

		std::vector<std::vector<Buffer*>> m_MaterialData; // 1 per entity per frame

		std::vector<std::vector<Buffer*>> m_TransformData; // 1 per frame per entity

		std::vector<std::vector<Buffer*>> m_VertexData; // 1 per frame per entity

		std::vector<std::vector<Buffer*>> m_IndexData; // 1 per frame per entity

	public:
		DrawStreamBufferPool(Device* device);
		~DrawStreamBufferPool();

	public:
		void AllocateAllGlobalData();
		void AllocateAllVertexAndIndexData(u32 count);

		std::vector<Buffer*>& CreateMaterialData();
		std::vector<Buffer*>& CreateTransformData();

		std::vector<Buffer*>& GetAllGlobalData();
		GlobalData* GetGlobalData(u32 frame);

		MaterialData* GetMaterialData(u32 frame, u32 index);
		TransformData* GetTransformData(u32 frame, u32 index);

		std::vector<Buffer*>& GetAllVertexData(u32 pipelineIndex);
		VertexData* GetVertexData(u32 frame, u32 index);

		std::vector<Buffer*>& GetAllIndexData(u32 pipelineIndex);
		IndexData* GetIndexData(u32 frame, u32 index);
	};
};
