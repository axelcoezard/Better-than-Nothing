#pragma once

#include "GlobalUniforms.hpp"
#include "DynamicUniforms.hpp"

namespace BetterThanNothing
{
	class Device;
	class SwapChain;

	/**
	 * @brief The uniforms is pool used to store the global and dynamic uniforms
	 * @note The global uniforms are the same for all entities, 1 per frame (camera, lights, etc.)
	 * @note The dynamic uniforms are different for each entity, 1 per entity per frame (model matrix, material, etc.)
	 */
	class UniformsPool
	{
	private:
		Device* m_Device;

		u32 m_Size;
		u32 m_Capacity;

		std::vector<Buffer*> m_GlobalUniforms; // 1 per frame
		std::vector<std::vector<Buffer*>> m_DynamicUniforms; // 1 per entity per frame

	public:
		UniformsPool(Device* device);
		~UniformsPool();

	private:
		void CreateUniformsPool(u32 newCapacity);
		void DestroyUniformsPool();

		void AllocateAllGlobalUniforms();

	public:
		void ExtendUniformsPool();
		std::vector<Buffer*>& CreateDynamicUniforms();

		std::vector<Buffer*>& GetAllGlobalUniforms();
		GlobalUniforms* GetGlobalUniforms(u32 frame);
		DynamicUniforms* GetDynamicUniforms(u32 frame, u32 index);

		bool ShouldExtends() const;

		u32 GetSize() const;
		u32 GetCapacity() const;
	};
};
